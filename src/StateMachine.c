/* 
 * File:   StateMachine.h
 * Author: Luke
 *
 * Created on 02 February 2016, 19:54
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "StateMachine.h"

/////////////////////////////////////DEFINES////////////////////////////////////

#define pollTMR_period 0xFFFF

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

/*state_conditions_t state_conditions;
state_t Curr_State, Next_State, Prev_State;*/

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

//////////////////////////////////FUNCTIONS/////////////////////////////////////

//dummy defines
char POLL_TIMER_INT_FL = 1;

/*state_t get_curr_state() {
    return Curr_State;
}
state_t get_next_state() {
    return Next_State;
}
state_t get_prev_state() {
    return Prev_State;
}
state_conditions_t get_conditions() {
    return state_conditions;
}

void set_curr_state(state_t state) {
    Curr_State = state;
}
void set_next_state(state_t state) {
    Next_State = state;
}
void set_prev_state(state_t state) {
    Prev_State = state;
}
void set_conditions(state_conditions_t conditions) {
    state_conditions = conditions;
}*/

/* -----------------------------------------------------------------------------
 * Function: state_handler()
 * 
 * Top level function for state machine - a new state starts execution here.
 * REMEMBER ALL THE DATA STORED LOCALLY IS SPECIFIC TO THE CURRENT STATE OF OPERATION
 * 
 * Local copy of SPI_newstate_ptr arguments are created.
 * Local struct for tracking variables is also created.
 * 
 * Poll_TMR is used to control the update rate of the controller.
 * A switch statement selects the correct processing for the current state.
 * 
 * Upon Poll_TMR, first sample all relevant sensors in an ATOMIC operation.
 * Then apply controller to sampled values.
 * Update outputs with new control variables.
 * 
 * Check for break condition to receive new state.
 * Check for break conditions to report state_complete to PI.
 * 
 * INPUTS: None
 * 
 * OUTPUTS: None
 * 
 */
void state_handler(spi_state_data * newstate_ptr) {
    // Create local copy of new_state arguments.
    // eg. copy arguments from global variables.
    spi_state_data local_currentstate_data = {
        .state                  = newstate_ptr->state,
        .state_data.data_type   = newstate_ptr->state_data.data_type,
        .state_data.value       = newstate_ptr->state_data.value
    };
    spi_state_data * local_currentstate_data_ptr = &local_currentstate_data;
    
    // Create local struct for any spi data to be written out.
    spi_data_out local_spi_data_out = {
        .datatype_signedint         = 0,
        .datatype_unsignedint       = 0
    };
    spi_data_out * local_spi_data_out_ptr = &local_spi_data_out;
    
    // Create local struct for storage of any tracking data.
    control_variables local_state_vars = {
        // initialise data
        .update_counter                 = 0,
        .general_break_condition        = STATE_CONTINUE,
        
        // set pid controller paramaters here
        .Controller1 = {0, 0, 0, 0, 0, 
                       {0},0,
                        0, 0, 0},   
        .pid_ctrl_ptr = &(local_state_vars.Controller1),
        
        // .psns_prev_digital_samples,   
        // .psns_adc_samples,                  
        
        .wheelencL_count                = 0,
        .wheelencR_count                = 0,
        
        .wheelencL_limit                = 0,
        .wheelencR_limit                = 0,
        
        .motor_L_desiredspeed           = 0,
        .motor_R_desiredspeed           = 0,
        .motor_dualspeed                = 0,
        
        .motor_L_direction              = FWD,
        .motor_R_direction              = FWD,
        .motor_dualdirection            = FWD,
        
        .usecompass                     = 0,        // disable by default
        .compass_currentheading         = 0,
        .compass_desiredheading         = 0,
        
        .usepsns                        = 0,        // disable by default
        .psns_currentheading            = 0,
        .psns_desiredheading            = 0,
    };
    local_state_vars.Controller1.p_e_ptr = local_state_vars.Controller1.p_e; // initialise pointer to recent errors array
    control_variables * local_state_vars_ptr = &local_state_vars;
    
    // Create local struct for storage of any break conditions.
    break_conditions_store local_state_break_conditions;
    break_conditions_store * local_state_break_conditions_ptr = &local_state_break_conditions;
    
    // Call state_setup function to initialise any modules necessary.
    switch_statesetup(local_state_vars_ptr,
                      local_currentstate_data_ptr,
                      local_state_break_conditions_ptr); 
    
    // Start poll_TMR
    unsigned int temp_pr = pollTMR_period;
    POllTMRinit(temp_pr);
    StartPollTMR();
    
    while(1) // remain in this function until break condition is triggered
    {
        // wait for poll_TMR ISR to set flag
        while(!IFS0bits.T1IF){};
        IFS0bits.T1IF = 0; // reset flag
        
        // atomically copy all sensor values to local data struct
        atomic_sensorcopy(local_state_vars_ptr);
        
        // branch to state-specific control algorithms
        switch_statecontrol(local_state_vars_ptr,
                            local_currentstate_data_ptr,
                            local_spi_data_out_ptr);
        
        // Check general break condition
        if (local_state_vars.general_break_condition == STATE_BREAK) {break;};
        // Check for break conditions (intersection, collision, cube, distance, angle etc.)
        switch_statebreak(local_state_vars_ptr,
                          local_currentstate_data_ptr,
                          local_state_break_conditions_ptr);
    
        // update loop counter
        local_state_vars_ptr->update_counter++;
    } // while(1)
    // breakcondition has been triggered
    
    // set all outputs to off
    
    // write output data to spi if appropriate
    Write_SPI(&DONE, 1);
}

/* -----------------------------------------------------------------------------
 * Function: atomic_sensorcopy(control_variables * local_state_vars_ptr)
 * 
 * Copies sensor data to local storage.
 * 
 * INPUTS: local_state_vars_ptr
 *  
 * OUTPUTS: none
 */
void atomic_sensorcopy(control_variables * local_state_vars_ptr)
{
    // disable interrupts
    copyencdr_tolocal(local_state_vars_ptr);

    if (local_state_vars_ptr->usepsns){  // only read in data if the state requires it
    copypsns_tolocal(local_state_vars_ptr);
    }
    if (local_state_vars_ptr->usecompass){
    copycompass_tolocal(local_state_vars_ptr);
    }
    // enable interrupts
}

/* -----------------------------------------------------------------------------
 * Function: copyencdr_tolocal(control_variables * local_state_vars_ptr)
 * 
 * This function copys the current sensor data to the local storage struct.
 * This function must execute atomically so data cannot change while being copied.
 * 
 * Encoders are read in for every possible state
 * 
 * INPUTS: local_state_vars_ptr, access to all global sensors/ sensor data
 * 
 * OUTPUTS: none
 */
void copyencdr_tolocal(control_variables * local_state_vars_ptr)
{
    // now read in/copy new sensor data
    local_state_vars_ptr->wheelencL_count = GLOBAL_enc1_count;
    local_state_vars_ptr->wheelencR_count = GLOBAL_enc2_count;
}

/* -----------------------------------------------------------------------------
 * Function: copysensor_tolocal(control_variables * local_state_vars_ptr)
 * 
 * This function copys the current sensor data to the local storage struct.
 * This function must execute atomically so data cannot change while being copied.
 * 
 * INPUTS: local_state_vars_ptr, access to all global sensors/ sensor data
 * 
 * OUTPUTS: none
 */
void copypsns_tolocal(control_variables * local_state_vars_ptr)
{
    // sample adc and read data in
    adc_linetrackinginit();
    unsigned int tempBuffer[4];
    unsigned int * tempBuffer_ptr = tempBuffer;
    adc_linetracking_sample(tempBuffer_ptr);
    
    unsigned int i = 0;
    for (i=0;i<4;i++)
    {
        local_state_vars_ptr->psns_adc_samples[i] = tempBuffer[i];
    }
    
    
    
    // read L,R,front sensor data into array under current update_counter
    unsigned int uc = local_state_vars_ptr->update_counter;
    unsigned int readL = ReadSENSL();/* left sensor read */
    unsigned int readR = ReadSENSR();/* right sensor read */
    unsigned int readF = ReadSENSF();/* front sensor read */
    
    
    WriteSENSLBuffer(readL);
    WriteSENSRBuffer(readR);
    WriteSENSFBuffer(readF);
}


/* -----------------------------------------------------------------------------
 * Function: copycompass_tolocal(control_variables * local_state_vars_ptr)
 * 
 * This function copys the current sensor data to the local storage struct.
 * This function must execute atomically so data cannot change while being copied.
 * 
 * Compass is seperated out so that it will only read in data if new data is available.
 * If a certain state does not use the compass, it will never be read in.
 * 
 * INPUTS: local_state_vars_ptr, access to all global sensors/ sensor data
 * 
 * OUTPUTS: none
 */
void copycompass_tolocal(control_variables * local_state_vars_ptr)
{
    // now read in/copy new sensor data
    local_state_vars_ptr->compass_currentheading = calculateHeading();
}

/* -----------------------------------------------------------------------------
 * Function: switch_statebreak(control_variables * local_state_vars_ptr,
 *                             spi_state_data * local_currentstate_data_ptr);
 * 
 * Function switches into the appropriate break condition for the current state.
 * If a break condition is reached then the general break condition is set.
 */
void switch_statebreak(control_variables * local_state_vars_ptr,
                       spi_state_data * local_currentstate_data_ptr,
                       break_conditions_store * local_state_break_conditions_ptr)
{
    //execute a different function based on state
    switch (local_currentstate_data_ptr->state)
    { 
        default:  // Default state is stopped/              
            //STOPPED
            break;

        case STOPPED:           
            //SPI transfer
            break;

        //Open Loop States//////////////////////////////////////////////////////        
        case OL_FORWARD:                //Open Loop Forward drive  
            // none
            break;
        case OL_REVERSE:                //Open Loop Reverse  
            // none
            break;

        //Closed Loop with Compass states///////////////////////////////////////
        case COMP_FORWARD:              //Closed Loop With Compass Forward drive 
            bc_counts_LandR(local_state_vars_ptr); 
            break;
        case COMP_LEFT:                 //Closed Loop With Compass Turn angle  
            angle_smallerror(local_state_vars_ptr);      
            break;
        case COMP_RIGHT:                 //Closed Loop With Compass Turn angle  
            angle_smallerror(local_state_vars_ptr);      
            break;    
        case COMP_REVERSE:              //Closed Loop With Compass Reverse   
            bc_counts_LandR(local_state_vars_ptr);
            break;
        case COMP_REV_LEFT:             //Closed Loop With Compass Reverse Left Turn (90) 
            angle_smallerror(local_state_vars_ptr);
            break;
        case COMP_REV_RIGHT:            //Closed Loop With Compass Reverse Right Turn (90)
            angle_smallerror(local_state_vars_ptr);
            break;

        //Closed Loop with Encoders states//////////////////////////////////////
        case ECDR_FORWARD:              //Closed Loop With Encoders Forward drive
            bc_counts_LandR(local_state_vars_ptr);
            break;
        case ECDR_LEFT:                 //Closed Loop With Encoders Forwards Left turn (90) 
            bc_counts_LandR(local_state_vars_ptr);  
            break;
        case ECDR_RIGHT:                //Closed Loop With Encoders Forwards Right turn (90)
            bc_counts_LandR(local_state_vars_ptr);  
            break;
        case ECDR_REVERSE:              //Closed Loop With Encoders Reverse   
            bc_counts_LandR(local_state_vars_ptr);  
            break;
        case ECDR_REV_LEFT:             //Closed Loop With Encoders Reverse Left Turn (90)
            bc_counts_R(local_state_vars_ptr);
            break;
        case ECDR_REV_RIGHT:            //Closed Loop With Encoders Reverse Right Turn (90)
            bc_counts_L(local_state_vars_ptr);
            break;

        //Closed Loop with Analog Sensors states////////////////////////////////
        case PSNS_FORWARD:                              //Closed Loop With PhotoSensors Forward drive   
            bc_counts_LandR(local_state_vars_ptr);   
            break;
        //Closed Loop with Analog Sensors states////////////////////////////////
        case PSNS_FORWARD_JUNCTION_DETECT:              //Closed Loop With PhotoSensors and detecting junction   
               
            break;  
    }
}
/* -----------------------------------------------------------------------------
 * Function: pid_updatemotors_fwd(control_variables * local_state_vars_ptr)
 * 
 * Update motor speeds based on newly generated control variable
 * 
 * INPUTS: ptr to local_state_vars
 */
void pid_updatemotors_fwd(control_variables * local_state_vars_ptr)
{
    int decreasedSpeed_temp = local_state_vars_ptr->motor_dualspeed - local_state_vars_ptr->Controller1.cv;
    int increasedSpeed_temp = local_state_vars_ptr->motor_dualspeed + local_state_vars_ptr->Controller1.cv;
    
    
    
//    if (local_state_vars_ptr->Controller1.cv <= 0) // less than 0 - turn right
//    {
        L_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                  FWD, 
                                  decreasedSpeed_temp);
        
        R_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                  FWD, 
                                  increasedSpeed_temp);
//    }
//    else
//    {
//        L_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
//                                  FWD, 
//                                  decreasedSpeed_temp);
//        
//        R_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
//                                  FWD, 
//                                  increasedSpeed_temp);
//    }
}

/* -----------------------------------------------------------------------------
 * Function: pid_updatemotors_rev(control_variables * local_state_vars_ptr)
 * 
 * Update motor speeds based on newly generated control variable. This function
 * is suitable for reversing while tracking a heading.
 * 
 * INPUTS: ptr to local_state_vars
 */
void pid_updatemotors_rev(control_variables * local_state_vars_ptr)
{
    int decreasedSpeed_temp = local_state_vars_ptr->motor_dualspeed - local_state_vars_ptr->Controller1.cv;
    int increasedSpeed_temp = local_state_vars_ptr->motor_dualspeed + local_state_vars_ptr->Controller1.cv;
    
    if (local_state_vars_ptr->Controller1.cv <= 0) // less than 0 - turn right
    {
        L_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                  REV, 
                                  increasedSpeed_temp);
        
        R_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                  REV, 
                                  decreasedSpeed_temp);
    }
    else
    {
        L_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                  REV, 
                                  decreasedSpeed_temp);
        
        R_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                  REV, 
                                  increasedSpeed_temp);
    }
}

/* -----------------------------------------------------------------------------
 * Function: pid_updatemotors_turn(control_variables * local_state_vars_ptr)
 * 
 * Update motor speeds based on newly generated control variable, to turn 
 * towards a new given heading.
 * 
 * INPUTS: ptr to local_state_vars
 */
void pid_updatemotors_turn(control_variables * local_state_vars_ptr)
{
    int decreasedSpeed_temp = local_state_vars_ptr->motor_dualspeed - local_state_vars_ptr->Controller1.cv;
    int increasedSpeed_temp = local_state_vars_ptr->motor_dualspeed + local_state_vars_ptr->Controller1.cv;
    
    if (local_state_vars_ptr->Controller1.cv <= 0)          // less than 0 - turn right
    {
        L_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                  FWD, 
                                  increasedSpeed_temp);
        
        R_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                  REV, 
                                  decreasedSpeed_temp);
    }
    else                                                    // =0 or >0, turn left
    {
        L_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                  REV, 
                                  decreasedSpeed_temp);
        
        R_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                  FWD, 
                                  increasedSpeed_temp);
    }
}

/* -----------------------------------------------------------------------------
 * Function pid_updatemotors_linefollow
 * 
 * This function will allow the motors to spin both backwards and forwards to
 * direct the robot.
 * 
 */
void pid_updatemotors_linefollow(control_variables * local_state_vars_ptr)
{
    int decreasedSpeed_temp = local_state_vars_ptr->motor_dualspeed - local_state_vars_ptr->Controller1.cv;
    int increasedSpeed_temp = local_state_vars_ptr->motor_dualspeed + local_state_vars_ptr->Controller1.cv;
    
    int decreasedSpeed_modulus = abs(decreasedSpeed_temp);   
    int increasedSpeed_modulus = abs(increasedSpeed_temp);
    
    // both speeds positive -> both wheels turn in same direction.
    if(decreasedSpeed_temp > 0 && increasedSpeed_temp > 0)
    {
//        // now check which direction to turn
//        if (local_state_vars_ptr->Controller1.cv <= 0)          // less than 0 - turn right
//        {
//            L_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
//                                      FWD, 
//                                      increasedSpeed_temp);
//
//            R_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
//                                      FWD, 
//                                      decreasedSpeed_temp);
//        }
//        else                                                    // =0 or >0, turn left
//        {
            L_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                      FWD, 
                                      decreasedSpeed_temp);

            R_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                      FWD, 
                                      increasedSpeed_temp);
//        }
    }
    
    // decreased speed is negative -> turn that wheel in reverse
    if(decreasedSpeed_temp < 0 || increasedSpeed_temp < 0)
    {
        // now check which direction to turn
        if (local_state_vars_ptr->Controller1.cv <= 0)          // less than 0 - turn right
        {
            L_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                      FWD, 
                                      decreasedSpeed_modulus);

            R_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                      REV, 
                                      increasedSpeed_modulus);
        }
        else                                                    // =0 or >0, turn left
        {
            L_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                      REV, 
                                      decreasedSpeed_modulus);

            R_motor_acceltoconstSpeed(local_state_vars_ptr->update_counter,
                                      FWD, 
                                      increasedSpeed_modulus);
        }
    }
} 

