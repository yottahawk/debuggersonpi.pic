/*
 * File:   states_setup.c
 * Author: hc139927
 *
 * Created on 24 February 2016, 10:59
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "states_setup.h"

/////////////////////////////////////DEFINES////////////////////////////////////

// Speed is within the range 1-500, with 500 being that fastest possible speed.
#define speed_LEVEL_1 100
#define speed_med 300
#define speed_fast 450

// PID controller params - linetracking
#define linetracking_kp           50
#define linetracking_ki           5
#define linetracking_ctrl_max     500 
#define linetracking_ctrl_min    -500

// PID controller params - turning
#define turning_kp           1
#define turning_ki           1
#define turning_ctrl_max     800 
#define turning_ctrl_min    -800

// PID controller params - turning

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

/* -----------------------------------------------------------------------------
 * Function: state_switch(control_variables local_state_vars)
 * 
 * This function is called when the poll_TMR triggers a new update, and switches
 * the appropriate control algorithm into the loop.
 * 
 * INPUTS: spi_newstate, state_vars and state_break_condition structs.
 * 
 * OUTPUTS: initialise state_vars and state_break_condition structs.
 */
void switch_statesetup(control_variables * local_state_vars_ptr,
                       spi_state_data * local_currentstate_data_ptr,
                       break_conditions_store * local_state_break_conditions_ptr)                     
{  
//execute a different function based on state
    switch (local_currentstate_data_ptr->state)
    { 
        default:  // Default state is stopped/              
            setup_state_stopped();        //Stationary
            break;

        case STOPPED:           
            setup_state_stopped();        //Stationary
            break;

        //Open Loop States//////////////////////////////////////////////////////        
        case OL_FORWARD:                //Open Loop Forward drive       
            setup_state_ol_forward(local_currentstate_data_ptr,
                                   local_state_vars_ptr,
                                   local_state_break_conditions_ptr);    
            break;
        case OL_REVERSE:                //Open Loop Reverse   
            setup_state_ol_reverse(local_currentstate_data_ptr,
                                   local_state_vars_ptr,
                                   local_state_break_conditions_ptr);     
            break;

        //Closed Loop with Compass states///////////////////////////////////////
        case COMP_FORWARD:              //Closed Loop With Compass Forward drive 
            setup_state_comp_forward(local_currentstate_data_ptr,
                                     local_state_vars_ptr,
                                     local_state_break_conditions_ptr);  
            break;
        case COMP_LEFT:                 //Closed Loop With Compass Turn angle  
            setup_state_comp_turn(local_currentstate_data_ptr,
                                  local_state_vars_ptr,
                                  local_state_break_conditions_ptr);      
            break;
        case COMP_RIGHT:                 //Closed Loop With Compass Turn angle  
            setup_state_comp_turn(local_currentstate_data_ptr,
                                  local_state_vars_ptr,
                                  local_state_break_conditions_ptr);      
            break;    
        case COMP_REVERSE:              //Closed Loop With Compass Reverse   
            setup_state_comp_reverse(local_currentstate_data_ptr,
                                     local_state_vars_ptr,
                                     local_state_break_conditions_ptr); 
            break;
        case COMP_REV_LEFT:             //Closed Loop With Compass Reverse Left Turn (90) 
            setup_state_comp_rev_left(local_currentstate_data_ptr,
                                      local_state_vars_ptr,
                                      local_state_break_conditions_ptr);  
            break;
        case COMP_REV_RIGHT:            //Closed Loop With Compass Reverse Right Turn (90)
            setup_state_comp_rev_right(local_currentstate_data_ptr,
                                       local_state_vars_ptr,
                                       local_state_break_conditions_ptr);
            break;

        //Closed Loop with Encoders states//////////////////////////////////////
        case ECDR_FORWARD:              //Closed Loop With Encoders Forward drive
            setup_state_ecdr_forward(local_currentstate_data_ptr,
                                     local_state_vars_ptr,
                                     local_state_break_conditions_ptr);   
            break;
        case ECDR_LEFT:                 //Closed Loop With Encoders Forwards Left turn (90) 
            setup_state_ecdr_left(local_currentstate_data_ptr,
                                  local_state_vars_ptr,
                                  local_state_break_conditions_ptr);    
            break;
        case ECDR_RIGHT:                //Closed Loop With Encoders Forwards Right turn (90)
            setup_state_ecdr_right(local_currentstate_data_ptr,
                                   local_state_vars_ptr,
                                   local_state_break_conditions_ptr);    
            break;
        case ECDR_REVERSE:              //Closed Loop With Encoders Reverse   
            setup_state_ecdr_reverse(local_currentstate_data_ptr,
                                     local_state_vars_ptr,
                                     local_state_break_conditions_ptr);   
            break;
        case ECDR_REV_LEFT:             //Closed Loop With Encoders Reverse Left Turn (90)
            setup_state_ecdr_rev_left(local_currentstate_data_ptr,
                                      local_state_vars_ptr,
                                      local_state_break_conditions_ptr);  
            break;
        case ECDR_REV_RIGHT:            //Closed Loop With Encoders Reverse Right Turn (90)
            setup_state_ecdr_rev_right(local_currentstate_data_ptr,
                                       local_state_vars_ptr,
                                       local_state_break_conditions_ptr); 
            break;

        //Closed Loop with Analog Sensors states////////////////////////////////
        case PSNS_FORWARD:              //Closed Loop With PhotoSensors Forward drive   
            setup_state_psns_forward(local_currentstate_data_ptr,
                                     local_state_vars_ptr,
                                     local_state_break_conditions_ptr);   
            break;
        //Closed Loop with Analog Sensors states////////////////////////////////
        case PSNS_FORWARD_JUNCTION_DETECT:              //Closed Loop With PhotoSensors and detecting junction   
            setup_state_psns_forward_junctiondetect(local_currentstate_data_ptr,
                                                    local_state_vars_ptr,
                                                    local_state_break_conditions_ptr);   
            break;  
    }   
} // switch(Curr_State)

/* -----------------------------------------------------------------------------
 * Function: setup_state_stopped()
 * 
 * Default setup function for the stopped state.
 * 
 */
void setup_state_stopped()
{
    
}

/* -----------------------------------------------------------------------------
 * Function: setup_state_ol_forward(spi_state_data * local_currentstate_data_ptr,
 *                                  control_variables * local_state_vars_ptr);
 * 
 * Setups the local tracking structs for the state ol_forward.
 * 
 * INPUTS: spi_state_data * local_currentstate_data_ptr,
 *         control_variables * local_state_vars_ptr
 * 
 * OUTPUTS: none
 */
void setup_state_ol_forward(spi_state_data * local_currentstate_data_ptr,
                            control_variables * local_state_vars_ptr,
                            break_conditions_store * local_state_break_conditions_ptr)
{
    // setup local data structures
    local_state_vars_ptr->motor_dualspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_dualdirection       = FWD;
    
    // setup break conditions
    // none
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_ecdr_left(spi_state_data * local_currentstate_data_ptr,
                           control_variables * local_state_vars_ptr,
                           break_conditions_store * local_state_break_conditions_ptr)
{
    // setup local data structures
    local_state_vars_ptr->motor_R_desiredspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_R_direction              = FWD;
    
    // setup break conditions
    // correct number of counts on right wheel
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_ecdr_right(spi_state_data * local_currentstate_data_ptr,
                            control_variables * local_state_vars_ptr,
                            break_conditions_store * local_state_break_conditions_ptr)
{
    // setup local data structures
    local_state_vars_ptr->motor_L_desiredspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_L_direction              = FWD;
    
    // setup break conditions
    // correct number of counts on left wheel
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_ol_reverse(spi_state_data * local_currentstate_data_ptr,
                            control_variables * local_state_vars_ptr,
                            break_conditions_store * local_state_break_conditions_ptr)
{
    // setup local data structures
    local_state_vars_ptr->motor_dualspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_dualdirection       = REV;
    
    // setup break conditions
    // none
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_ecdr_rev_left(spi_state_data * local_currentstate_data_ptr,
                               control_variables * local_state_vars_ptr,
                               break_conditions_store * local_state_break_conditions_ptr)
{
    // setup local data structures
    local_state_vars_ptr->motor_R_desiredspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_R_direction              = REV;
    
    // setup break conditions
    // correct number of counts on right wheel
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_ecdr_rev_right(spi_state_data * local_currentstate_data_ptr,
                                control_variables * local_state_vars_ptr,
                                break_conditions_store * local_state_break_conditions_ptr)
{
    // setup local data structures
    local_state_vars_ptr->motor_L_desiredspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_L_direction              = REV;
    
    // setup break conditions
    // correct number of counts on left wheel
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_comp_forward(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr,
                              break_conditions_store * local_state_break_conditions_ptr)
{
    // setup "local_state_vars"
    local_state_vars_ptr->motor_dualspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_dualdirection       = FWD;
    
    int th = getHeading();
    local_state_vars_ptr->compass_desiredheading    = th;   // stay on current heading, just reverse
    local_state_vars_ptr->usecompass                = USESENSORS_TRUE;
    
    local_state_vars_ptr->Controller1.sp            = local_state_vars_ptr->compass_desiredheading;
    local_state_vars_ptr->Controller1.kp            = turning_kp;
    local_state_vars_ptr->Controller1.ki            = turning_ki;
    local_state_vars_ptr->Controller1.max           = turning_ctrl_max;
    local_state_vars_ptr->Controller1.min           = turning_ctrl_min;

    // setup break conditions
    //
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_comp_turn(spi_state_data * local_currentstate_data_ptr,
                           control_variables * local_state_vars_ptr,
                           break_conditions_store * local_state_break_conditions_ptr)
{
    // setup "local_state_vars"
    
    // no need to set motor direction - this is chosen depending on the cv
    int th = getHeading();
    int temph = 0;
    if (local_currentstate_data_ptr->state == COMP_LEFT)
    {
        local_state_vars_ptr->motor_dualspeed           = speed_LEVEL_1;
        temph = addHeadings(th, -90); // left is -90
    }
    if (local_currentstate_data_ptr->state == COMP_RIGHT)
    {
        local_state_vars_ptr->motor_dualspeed           = speed_LEVEL_1;
        temph = addHeadings(th, 90);  // right is +90
    }
    local_state_vars_ptr->compass_desiredheading    = temph; 
    local_state_vars_ptr->usecompass                = USESENSORS_TRUE;
    
    local_state_vars_ptr->Controller1.sp            = local_state_vars_ptr->compass_desiredheading;
    local_state_vars_ptr->Controller1.kp            = turning_kp;
    local_state_vars_ptr->Controller1.ki            = turning_ki;
    local_state_vars_ptr->Controller1.max           = turning_ctrl_max;
    local_state_vars_ptr->Controller1.min           = turning_ctrl_min;

    // setup break conditions
    // error is stable within a certain bound
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_comp_reverse(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr,
                              break_conditions_store * local_state_break_conditions_ptr)
{
    // setup "local_state_vars"
    local_state_vars_ptr->motor_dualspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_dualdirection       = REV;
    
    int th = getHeading();
    local_state_vars_ptr->compass_desiredheading    = th;   // stay on current heading, just reverse
    local_state_vars_ptr->usecompass                = USESENSORS_TRUE;
    
    local_state_vars_ptr->Controller1.sp            = local_state_vars_ptr->compass_desiredheading;
    local_state_vars_ptr->Controller1.kp            = turning_kp;
    local_state_vars_ptr->Controller1.ki            = turning_ki;
    local_state_vars_ptr->Controller1.max           = turning_ctrl_max;
    local_state_vars_ptr->Controller1.min           = turning_ctrl_min;

    // setup break conditions
    // 
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}


void setup_state_comp_rev_left(spi_state_data * local_currentstate_data_ptr,
                               control_variables * local_state_vars_ptr,
                               break_conditions_store * local_state_break_conditions_ptr)     
{
     // setup "local_state_vars"
    local_state_vars_ptr->motor_R_desiredspeed      = speed_LEVEL_1;
    
    int th = getHeading();
    local_state_vars_ptr->compass_desiredheading    = addHeadings(th, -90); // minus 90 = rotate right
    local_state_vars_ptr->usecompass                = USESENSORS_TRUE;
    
    local_state_vars_ptr->Controller1.sp            = local_state_vars_ptr->compass_desiredheading;
    local_state_vars_ptr->Controller1.kp            = turning_kp;
    local_state_vars_ptr->Controller1.ki            = turning_ki;
    local_state_vars_ptr->Controller1.max           = turning_ctrl_max;
    local_state_vars_ptr->Controller1.min           = turning_ctrl_min;

    // setup break conditions
    // error is stable within a certain bound
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_comp_rev_right(spi_state_data * local_currentstate_data_ptr,
                                control_variables * local_state_vars_ptr,
                                break_conditions_store * local_state_break_conditions_ptr)
{
    // setup "local_state_vars"
    local_state_vars_ptr->motor_L_desiredspeed      = speed_LEVEL_1;
    
    int th = getHeading();
    local_state_vars_ptr->compass_desiredheading    = addHeadings(th, 90); // add 90 = rotate right
    local_state_vars_ptr->usecompass                = USESENSORS_TRUE;
    
    local_state_vars_ptr->Controller1.sp            = local_state_vars_ptr->compass_desiredheading;
    local_state_vars_ptr->Controller1.kp            = turning_kp;
    local_state_vars_ptr->Controller1.ki            = turning_ki;
    local_state_vars_ptr->Controller1.max           = turning_ctrl_max;
    local_state_vars_ptr->Controller1.min           = turning_ctrl_min;

    // setup break conditions
    // error is stable within a certain bound
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_ecdr_forward(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr,
                              break_conditions_store * local_state_break_conditions_ptr)
{
    // setup "local_state_vars"
    local_state_vars_ptr->motor_dualspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_dualdirection       = FWD;
    
    local_state_vars_ptr->wheelencL_limit           = local_currentstate_data_ptr->state_data.value;
    local_state_vars_ptr->wheelencR_limit           = local_currentstate_data_ptr->state_data.value;

    // setup break conditions
    // count condition is reached
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_ecdr_reverse(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr,
                              break_conditions_store * local_state_break_conditions_ptr)
{
    // setup "local_state_vars"
    local_state_vars_ptr->motor_dualspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_dualdirection       = REV;
    
    local_state_vars_ptr->wheelencL_limit           = local_currentstate_data_ptr->state_data.value;
    local_state_vars_ptr->wheelencR_limit           = local_currentstate_data_ptr->state_data.value;

    // setup break conditions
    // count condition is reached
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_psns_forward(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr,
                              break_conditions_store * local_state_break_conditions_ptr)
{
    // setup "local_state_vars"
    local_state_vars_ptr->motor_dualspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_dualdirection       = FWD;
    
    local_state_vars_ptr->wheelencL_limit           = local_currentstate_data_ptr->state_data.value;
    local_state_vars_ptr->wheelencR_limit           = local_currentstate_data_ptr->state_data.value;
    
    local_state_vars_ptr->usepsns                   = USESENSORS_TRUE;
    local_state_vars_ptr->psns_desiredheading       = 0;
    
    // assume starting facing correct direction....
    local_state_vars_ptr->Controller1.sp            = local_state_vars_ptr->psns_desiredheading; 
    local_state_vars_ptr->Controller1.kp            = linetracking_kp;
    local_state_vars_ptr->Controller1.ki            = linetracking_ki;
    local_state_vars_ptr->Controller1.max           = linetracking_ctrl_max;
    local_state_vars_ptr->Controller1.min           = linetracking_ctrl_min;
    
    // setup break conditions
    // count condition is reached
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}

void setup_state_psns_forward_junctiondetect(spi_state_data * local_currentstate_data_ptr,
                                             control_variables * local_state_vars_ptr,
                                             break_conditions_store * local_state_break_conditions_ptr)
{
    // setup "local_state_vars"
    local_state_vars_ptr->motor_dualspeed           = speed_LEVEL_1;
    local_state_vars_ptr->motor_dualdirection       = FWD;
    
    local_state_vars_ptr->wheelencL_limit           = local_currentstate_data_ptr->state_data.value;
    local_state_vars_ptr->wheelencR_limit           = local_currentstate_data_ptr->state_data.value;
    
    local_state_vars_ptr->usepsns                   = USESENSORS_TRUE;
    local_state_vars_ptr->psns_desiredheading       = 0;
    
    // assume starting facing correct direction....
    local_state_vars_ptr->Controller1.sp            = local_state_vars_ptr->psns_desiredheading; 
    local_state_vars_ptr->Controller1.kp            = linetracking_kp;
    local_state_vars_ptr->Controller1.ki            = linetracking_ki;
    local_state_vars_ptr->Controller1.max           = linetracking_ctrl_max;
    local_state_vars_ptr->Controller1.min           = linetracking_ctrl_min;
    
    // setup break conditions
    // junction is detected !!
    
    // setup interrupts, enables, etc.
    enableMotorPSU();
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}