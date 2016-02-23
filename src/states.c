/* 
 * File:   states.c
 * Author: Harry
 *
 * Created on February 20, 2016, 10:05 PM
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "states.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

/* -----------------------------------------------------------------------------
 * Function: state_switch(control_variables local_state_vars)
 * 
 * This function is called when the poll_TMR triggers a new update, and switches
 * the appropriate control algorithm into the loop.
 * 
 * INPUTS: all the local state tracking variables from previous loop execution
 * 
 * OUTPUTS: tracking variables are updated
 */
void switch_statecontrol(control_variables * local_state_vars_ptr,
                         spi_state_data * local_state_data_ptr,
                         spi_data_out * local_spi_data_out_ptr)
{  
//execute a different function based on state
    switch (local_state_data_ptr->state)
    { 
        default:  // Default state is stopped/              
            state_stopped();        //Stationary
            break;

        case STOPPED:           
            state_stopped();        //Stationary
            break;

        //Open Loop States//////////////////////////////////////////////////////        
        case OL_FORWARD:                //Open Loop Forward drive       
            state_ol_forward(control_variables * local_state_vars_ptr);    
            break;
//        case OL_LEFT:                   //Open Loop Forwards Left turn (90)         
//            state_ol_left(control_variables * local_state_vars_ptr);        
//            break;
//        case OL_RIGHT:                  //Open Loop Forwards Right turn (90)         
//            state_ol_right(control_variables * local_state_vars_ptr);       
//            break;
        case OL_REVERSE:                //Open Loop Reverse   
            state_ol_reverse(control_variables * local_state_vars_ptr);     
            break;
//        case OL_REV_LEFT:               //Open Loop Reverse Left Turn (90)     
//            state_ol_rev_left(control_variables * local_state_vars_ptr);    
//            break;
//        case OL_REV_RIGHT:              //Open Loop Reverse Right Turn (90)
//            state_ol_rev_right(control_variables * local_state_vars_ptr);   
//            break;

        //Closed Loop with Compass states///////////////////////////////////////
        case COMP_FORWARD:              //Closed Loop With Compass Forward drive 
            state_comp_forward(control_variables * local_state_vars_ptr);   
            break;
        case COMP_TURN:                 //Closed Loop With Compass Turn angle  
            state_comp_turn(control_variables * local_state_vars_ptr);      
            break;
        case COMP_REVERSE:              //Closed Loop With Compass Reverse   
            state_comp_reverse(control_variables * local_state_vars_ptr);   
            break;
        case COMP_REV_LEFT:             //Closed Loop With Compass Reverse Left Turn (90) 
            state_comp_rev_left(control_variables * local_state_vars_ptr);  
            break;
        case COMP_REV_RIGHT:            //Closed Loop With Compass Reverse Right Turn (90)
            state_comp_rev_right(control_variables * local_state_vars_ptr); 
            break;

        //Closed Loop with Encoders states//////////////////////////////////////
        case ECDR_FORWARD:              //Closed Loop With Encoders Forward drive
            state_ecdr_forward(control_variables * local_state_vars_ptr);   
            break;
        case ECDR_LEFT:                 //Closed Loop With Encoders Forwards Left turn (90) 
            state_ecdr_left(control_variables * local_state_vars_ptr);      
            break;
        case ECDR_RIGHT:                //Closed Loop With Encoders Forwards Right turn (90)
            state_ecdr_right(control_variables * local_state_vars_ptr);     
            break;
        case ECDR_REVERSE:              //Closed Loop With Encoders Reverse   
            state_ecdr_reverse(control_variables * local_state_vars_ptr);   
            break;
        case ECDR_REV_LEFT:             //Closed Loop With Encoders Reverse Left Turn (90)
            state_ecdr_rev_left(control_variables * local_state_vars_ptr);  
            break;
        case ECDR_REV_RIGHT:            //Closed Loop With Encoders Reverse Right Turn (90)
            state_ecdr_rev_right(control_variables * local_state_vars_ptr); 
            break;

        //Closed Loop with Analog Sensors states////////////////////////////////
        case PSNS_FORWARD:              //Closed Loop With PhotoSensors Forward drive   
            state_psns_forward(control_variables * local_state_vars_ptr);   
            break;  
//        case PSNS_LEFT:                 //Closed Loop With PhotoSensors Forwards Left turn (90) 
//            state_psns_left(control_variables * local_state_vars_ptr);      
//            break;
//        case PSNS_RIGHT:                //Closed Loop With PhotoSensors Forwards Right turn (90)
//            state_psns_right(control_variables * local_state_vars_ptr);     
//            break;
//        case PSNS_REVERSE:              //Closed Loop With PhotoSensors Reverse    
//            state_psns_reverse(control_variables * local_state_vars_ptr);   
//            break;
//        case PSNS_REV_LEFT:             //Closed Loop With PhotoSensors Reverse Left Turn (90)
//            state_psns_rev_left(control_variables * local_state_vars_ptr);  
//            break;
//        case PSNS_REV_RIGHT:            //Closed Loop With PhotoSensors Reverse Right Turn (90) 
//            state_psns_rev_right(control_variables * local_state_vars_ptr);  
//            break;

        case OPEN_GRABBER:      
            state_open_grabber();
            break;
        case CLOSE_GRABBER:     
            state_close_grabber();
            break;
        case READ_GRABBER:      
            state_read_grabber();
            break;

        //Motor Commands////////////////////////////////////////////////////////
        case WRITE_MOTOR_LEFT_FWD:  
            state_write_motor_left_fwd(control_variables * local_state_vars_ptr,
                                       spi_state_data * local_state_data_ptr);
            break;
        case WRITE_MOTOR_LEFT_REV:  
            state_write_motor_left_rev(control_variables * local_state_vars_ptr,
                                       spi_state_data * local_state_data_ptr);
            break;
        case WRITE_MOTOR_RIGHT_FWD: 
            state_write_motor_right_fwd(control_variables * local_state_vars_ptr,
                                        spi_state_data * local_state_data_ptr);
            break;
        case WRITE_MOTOR_RIGHT_REV: 
            state_write_motor_right_rev(control_variables * local_state_vars_ptr,
                                        spi_state_data * local_state_data_ptr);
            break;


        //Encoder Commands//////////////////////////////////////////////////////
//        case READ_ECDR1:        
//            state_read_ecdr1(control_variables * local_state_vars_ptr);
//            break;
        case READ_ECDR1_SUM:    
            state_read_ecdr1_sum(control_variables * local_state_vars_ptr, 
                                 spi_data_out * local_spi_data_out_ptr);
            break;
//        case READ_ECDR2:        
//            state_read_ecdr2(control_variables * local_state_vars_ptr);
//            break;
        case READ_ECDR2_SUM:    
            state_read_ecdr2_sum(control_variables * local_state_vars_ptr, 
                                 spi_data_out * local_spi_data_out_ptr);
            break;

        //Compass commands//////////////////////////////////////////////////////
        case READ_COMP:         
            state_read_comp(control_variables * local_state_vars_ptr, 
                            spi_data_out * local_spi_data_out_ptr);
            break;

        //Photosensor commands//////////////////////////////////////////////////
//        case READ_PSNS1:        
//            state_read_psns1(control_variables * local_state_vars_ptr);
//            break;
//        case READ_PSNS2:        
//            state_read_psns2(control_variables * local_state_vars_ptr);
//            break;
//        case READ_PSNS3:        
//            state_read_psns3(control_variables * local_state_vars_ptr);
//            break;
//        case READ_PSNS4:        
//            state_read_psns4(control_variables * local_state_vars_ptr);
//            break;
        case READ_PSNS_L:        
            state_read_psns_L(control_variables * local_state_vars_ptr, 
                              spi_data_out * local_spi_data_out_ptr);
            break;
        case READ_PSNS_R:        
            state_read_psns_R(control_variables * local_state_vars_ptr, 
                              spi_data_out * local_spi_data_out_ptr);
            break;
        case READ_PSNSFNT:      
            state_read_psnsfnt(control_variables * local_state_vars_ptr, 
                               spi_data_out * local_spi_data_out_ptr);
            break;
        case READ_PSNSCBE:      
            state_read_psnscbe(control_variables * local_state_vars_ptr, 
                               spi_data_out * local_spi_data_out_ptr);
            break;

        //Operate LED///////////////////////////////////////////////////////////
        case WRITE_LED:         
            state_write_led(control_variables * local_state_vars_ptr,
                            spi_state_data * local_state_data_ptr);
            break;

        //Read DIP Switches/////////////////////////////////////////////////////
        case READ_DIP:          
            state_read_dip(control_variables * local_state_vars_ptr,
                           spi_data_out * local_spi_data_out_ptr);
            break;
    } // switch(Curr_State)
}

/* -----------------------------------------------------------------------------
 * Function: state_stopped()
 * 
 * Placeholder function for a stopped state
 * 
 * INPTUTS: none
 * 
 * OUTPUTS: none
 */
void state_stopped(){};

/* -----------------------------------------------------------------------------
 * Function: state_ol_forward(control_variables local_state_vars)
 * 
 * Updates the robot drive to drive forwards in a straight line. 
 * 
 * INPUTS: Local state tracking variables
 * 
 * OUTPUTS: none
 */
void state_ol_forward(control_variables * local_state_vars_ptr)
{
    motors_dual_constspeed(motor_direction_type FWD,
                           local_state_vars_ptr->motor_dualspeed);
}

/* -----------------------------------------------------------------------------
 * Function: state_ecdr_left(control_variables * local_state_vars_ptr)
 * 
 * Uses open-loop control to execute a 90 degree turn to the left. The speed of 
 * the turn is controlled by the local_state_vars struct.
 * This function triggers the statehandler general break condition.
 * 
 * INPTUS: local_state_vars struct
 * 
 * OUTPUTS: none
 *
*/
void state_ecdr_left(control_variables * local_state_vars_ptr)
{
    // if encoder count not reached, keep driving wheel
    if (local_state_vars_ptr->wheelencL_count < local_state_vars_ptr->wheelencL_limit) 
    {
        L_motor_constSpeed(motor_direction_type REV,    // left mtr reverse
                           unsigned int local_state_vars_ptr->motor_L_desiredspeed);
    }
   
    if (local_state_vars_ptr->wheelencR_count < local_state_vars_ptr->wheelencR_limit)
    {
        R_motor_constSpeed(motor_direction_type FWD,    // right mtr forward
                       unsigned int local_state_vars_ptr->motor_R_desiredspeed);
    }
    
    // if both wheels reached desired count, trigger break condition
    if (local_state_vars_ptr->wheelencL_count > local_state_vars_ptr->wheelencL_limit &&
        local_state_vars_ptr->wheelencR_count > local_state_vars_ptr->wheelencR_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    }; 
}

/* -----------------------------------------------------------------------------
 * Function: state_ol_right(control_variables * local_state_vars_ptr)
 * 
 * Uses open-loop control to execute a 90 degree turn to the right. The speed of 
 * the turn is controlled by the local_state_vars struct.
 * This function triggers the statehandler general break condition.
 * 
 * INPTUS: local_state_vars struct
 * 
 * OUTPUTS: none
 *
*/
void state_ecdr_right(control_variables * local_state_vars_ptr)
{
    // if encoder count not reached, keep driving wheel
    if (local_state_vars_ptr->wheelencL_count < local_state_vars_ptr->wheelencL_limit) 
    {
        L_motor_constSpeed(motor_direction_type FWD,    // left mtr forward
                           unsigned int local_state_vars_ptr->motor_L_desiredspeed);
    }
   
    if (local_state_vars_ptr->wheelencR_count < local_state_vars_ptr->wheelencR_limit)
    {
        R_motor_constSpeed(motor_direction_type REV,    // right mtr reverse
                       unsigned int local_state_vars_ptr->motor_R_desiredspeed);
    }
    
    // if both wheels reached desired count, trigger break condition
    if (local_state_vars_ptr->wheelencL_count > local_state_vars_ptr->wheelencL_limit &&
        local_state_vars_ptr->wheelencR_count > local_state_vars_ptr->wheelencR_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    }; 
}

/* -----------------------------------------------------------------------------
 * Function: state_ol_reverse(control_variables * local_state_vars_ptr)
 * 
 * Open loop reverse in a straight line
 * 
 * INPUTS: local_state_vars
 * 
 * OUTPUTS: none
 */
void state_ol_reverse(control_variables * local_state_vars_ptr)
{
    motors_dual_constspeed(motor_direction_type REV,
                           local_state_vars_ptr->motor_dualspeed);
}

/* -----------------------------------------------------------------------------
 * Function: state_ecdr_rev_left(control_variables * local_state_vars_ptr)
 * 
 * Open loop reverse and turn left 90 deg.
 * This function triggers the statehandler general break condition.
 * 
 * INPUTS: local_state_vars
 * 
 * OUTPUTS: none
 */
void state_ecdr_rev_left(control_variables * local_state_vars_ptr)
{
    if (local_state_vars_ptr->wheelencR_count < local_state_vars_ptr->wheelencR_limit)
    {
        R_motor_constSpeed(motor_direction_type REV,    // right mtr reverse
                       unsigned int local_state_vars_ptr->motor_R_desiredspeed);
    }
    
    // if wheel reaches desired count, trigger break condition
    if (local_state_vars_ptr->wheelencR_count > local_state_vars_ptr->wheelencR_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    }; 
}

/* -----------------------------------------------------------------------------
 * Function: state_ol_rev_right(control_variables * local_state_vars_ptr)
 * 
 * Open loop reverse and turn right 90 deg.
 * This function triggers the statehandler general break condition.
 * 
 * INPUTS: local_state_vars
 * 
 * OUTPUTS: none
 */
void state_ecdr_rev_right(control_variables * local_state_vars_ptr)
{
    if (local_state_vars_ptr->wheelencL_count < local_state_vars_ptr->wheelencL_limit)
    {
        L_motor_constSpeed(motor_direction_type REV,    // right mtr reverse
                       unsigned int local_state_vars_ptr->motor_L_desiredspeed);
    }
    
    // if wheel reaches desired count, trigger break condition
    if (local_state_vars_ptr->wheelencL_count > local_state_vars_ptr->wheelencL_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    }; 
}

/* -----------------------------------------------------------------------------
 * Function: state_comp_forward(control_variables * local_state_vars_ptr);
 * 
 * Drives forward using compass as angular feedback.
 * 
 * INPUTS: local_state_vars
 * 
 * OUTPUTS: none
 */
void state_comp_forward(control_variables * local_state_vars_ptr)
{
    // pid setpoint (desired angle) is set in structure when initialised
    // pid_update calculates a new control variable and writes it into struct
    pid_update(local_state_vars_ptr->compass_currentheading,
               local_state_vars_ptr->pid_ctrl_ptr);
    
    pid_updatemotors_fwd(control_variables * local_state_vars_ptr);
}

/* -----------------------------------------------------------------------------
 * Function: state_comp_turn(control_variables * local_state_vars_ptr)
 * 
 * Makes a turn using the compass as angular feedback.
 * 
 * INPUTS: local_state_vars_ptr 
 * 
 * OUTPUTS: none
 */
void state_comp_turn(control_variables * local_state_vars_ptr)
{
    // pid setpoint (desired angle) is set in structure when initialised
    // pid_update calculates a new control variable and writes it into struct
    pid_update(local_state_vars_ptr->compass_currentheading,
               local_state_vars_ptr->pid_ctrl_ptr);
    
    // update motors
    pid_updatemotors_turn(control_variables * local_state_vars_ptr);
    
    // generate break condition if error is small. 
}

/* -----------------------------------------------------------------------------
 * Function: state_comp_reverse(control_variables * local_state_vars_ptr)
 * 
 * Reverse in a straight line using the compass as angular feedback.
 * Use a forward heading for the PID, but set the motors in reverse. 
 * Then, the steering inputs are reversed.
 * 
 * INPUTS: local_state_vars_ptr 
 * 
 * OUTPUTS: none
 */
void state_comp_reverse(control_variables * local_state_vars_ptr)
{
    // pid setpoint (desired angle) is set in structure when initialised
    // pid_update calculates a new control variable and writes it into struct
    pid_update(local_state_vars_ptr->compass_currentheading,
               local_state_vars_ptr->pid_ctrl_ptr);
    
    pid_updatemotors_rev(control_variables * local_state_vars_ptr);
    
    // generate break condition if error is small.
}

/* -----------------------------------------------------------------------------
 * Function: state_comp_rev_left(control_variables * local_state_vars_ptr)
 * 
 * Reverse to the left 90 degrees, and use the compass as angular feedback.
 * Rotate/turn by rotating one wheel only.
 * 
 * INPUTS: local_state_vars_ptr
 * 
 * OUTPUTS: none
 */
void state_comp_rev_left(control_variables * local_state_vars_ptr)
{
    // pid setpoint (desired angle) is set in structure when initialised
    // pid_update calculates a new control variable and writes it into struct
    pid_update(local_state_vars_ptr->compass_currentheading,
               local_state_vars_ptr->pid_ctrl_ptr);
    
    // update motors
    R_motor_acceltoconstSpeed(control_variables * local_state_vars_ptr,
                              motor_direction_type REV, 
                              unsigned int (local_state_vars_ptr->motor_dualspeed + local_state_vars_ptr->Controller1.cv));

    // generate break condition if error is small.
}

/* -----------------------------------------------------------------------------
 * Function: state_comp_rev_right(control_variables * local_state_vars_ptr)
 * 
 * Reverse to the right 90 degrees, and use the compass as angular feedback.
 * 
 * INPUTS: local_state_vars_ptr
 * 
 * OUTPUTS: none
 */
void state_comp_rev_right(control_variables * local_state_vars_ptr)
{
    // pid setpoint (desired angle) is set in structure when initialised
    // pid_update calculates a new control variable and writes it into struct
    pid_update(local_state_vars_ptr->compass_currentheading,
               local_state_vars_ptr->pid_ctrl_ptr);
    
    // update motors
    L_motor_acceltoconstSpeed(control_variables * local_state_vars_ptr,
                              motor_direction_type REV, 
                              unsigned int (local_state_vars_ptr->motor_dualspeed + local_state_vars_ptr->Controller1.cv));

    // generate break condition if error is small.
}

/* -----------------------------------------------------------------------------
 * Function: state_ecdr_forward(control_variables * local_state_vars_ptr)
 * 
 * Drive forward open_loop, until a count limit is reached.
 * 
 * INPTUS: local_state_vars_ptr
 * 
 * OUTPUTS: none 
 */
void state_ecdr_forward(control_variables * local_state_vars_ptr)
{
    // use the open-loop forward state
    state_ol_forward(control_variables * local_state_vars_ptr);
            
    // set break condition when count limit is reached
    if (local_state_vars_ptr->wheelencL_count > local_state_vars_ptr->wheelencL_limit ||
        local_state_vars_ptr->wheelencR_count > local_state_vars_ptr->wheelencR_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    };
}
        
/* -----------------------------------------------------------------------------
 * Function: state_ecdr_reverse(control_variables * local_state_vars_ptr)
 * 
 * Reverse open-loop, until a count limit is reached.
 * 
 * INPUTS: local_state_vars_ptr
 * 
 * OUTPUTS: none
 */
void state_ecdr_reverse(control_variables * local_state_vars_ptr)
{
    // use the open-loop reverse state
    state_ol_reverse(control_variables * local_state_vars_ptr);
    
    // set break condition when count limit is reached
    if (local_state_vars_ptr->wheelencL_count > local_state_vars_ptr->wheelencL_limit ||
        local_state_vars_ptr->wheelencR_count > local_state_vars_ptr->wheelencR_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    };
}

/* -----------------------------------------------------------------------------
 * Function: state_psns_forward(control_variables * local_state_vars_ptr); 
 * 
 * Moves the robot forward, while using the photosensors to estimate
 * the angular deviation, and a PID controller to correct the error.
 * 
 * INPUTS: local_state_vars_ptr
 * 
 * OUTPUT: none
 */
void state_psns_forward(control_variables * local_state_vars_ptr)
{
    // ADC sample data is already in buffer
    
    signed int diffs[2] = 0;
    signed int * diffs_ptr = &diffs;
    
    // calculate two differences
    linefollow_calcpairdiffs(local_state_vars_ptr->psns_adc_samples, diffs_ptr);
    
    // estimate angle from differences
    signed int psns_estimate_angle;
    psns_estimate_angle = linefollow_estimateangle_ldr(diffs_ptr);

    // input new angular error estimate into PID controller
    pid_update(psns_estimate_angle,
               local_state_vars_ptr->pid_ctrl_ptr);
    
    // generate break condition when encoder count is reached.
    if (local_state_vars_ptr->wheelencL_count > local_state_vars_ptr->wheelencL_limit ||
        local_state_vars_ptr->wheelencR_count > local_state_vars_ptr->wheelencR_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    };
}

/* -----------------------------------------------------------------------------
 * Function: state_write_motor_left_fwd(spi_state_data * local_state_data_ptr)
 * 
 * Writes a value to the left motor speed, turning it on in a forward direction.
 * 
 * INPUTS: local_state_data_ptr
 * 
 * OUTPUTS: none
 */
void state_write_motor_left_fwd(control_variables * local_state_vars_ptr,
                                spi_state_data * local_state_data_ptr)
{
    L_motor_constSpeed(motor_direction_type FWD, local_state_data_ptr->state_data->value);
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}

/* -----------------------------------------------------------------------------
 * Function: state_write_motor_left_rev(spi_state_data * local_state_data_ptr)
 * 
 * Writes a value to the left motor speed, turning it on in a reverse direction.
 * 
 * INPUTS: local_state_data_ptr
 * 
 * OUTPUTS: none
 */
void state_write_motor_left_rev(control_variables * local_state_vars_ptr,
                                spi_state_data * local_state_data_ptr)
{
    L_motor_constSpeed(motor_direction_type REV, local_state_data_ptr->state_data->value);
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}

/* -----------------------------------------------------------------------------
 * Function: state_write_motor_right_fwd(spi_state_data * local_state_data_ptr)
 * 
 * Writes a value to the right motor speed, turning it on in a forward direction.
 * 
 * INPUTS: local_state_data_ptr
 * 
 * OUTPUTS: none
 */
void state_write_motor_right_fwd(control_variables * local_state_vars_ptr,
                                spi_state_data * local_state_data_ptr)
{
    R_motor_constSpeed(motor_direction_type FWD, local_state_data_ptr->state_data->value);
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}

/* -----------------------------------------------------------------------------
 * Function: state_write_motor_left_rev(spi_state_data * local_state_data_ptr)
 * 
 * Writes a value to the right motor speed, turning it on in a reverse direction.
 * 
 * INPUTS: local_state_data_ptr
 * 
 * OUTPUTS: none
 */
void state_write_motor_right_rev(control_variables * local_state_vars_ptr,
                                spi_state_data * local_state_data_ptr)
{
    R_motor_constSpeed(motor_direction_type REV, local_state_data_ptr->state_data->value);
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}

/* -----------------------------------------------------------------------------
 * Function: state_read_ecdr1_sum(control_variables * local_state_vars_ptr);
 * 
 * Writes the current encoder1 value out to the PI over SPI.
 * The value is written to a temporary data structure. The actual SPI transfer 
 * is made when the break condition is triggered.
 * 
 * INPUTS: local_state_vars_ptr
 * 
 * OUTPUTS: none
 */
void state_read_ecdr1_sum(control_variables * local_state_vars_ptr, 
                          spi_data_out * local_spi_data_out_ptr)
{
    * local_spi_data_out_ptr->datatype_unsignedint = local_state_vars_ptr->wheelencL_count;
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}

/* -----------------------------------------------------------------------------
 * Function: state_read_ecdr2_sum(control_variables * local_state_vars_ptr);
 * 
 * Writes the current encoder2 value out to the PI over SPI.
 * The value is written to a temporary data structure. The actual SPI transfer 
 * is made when the break condition is triggered.
 * 
 * INPUTS: local_state_vars_ptr
 * 
 * OUTPUTS: none
 */
void state_read_ecdr2_sum(control_variables * local_state_vars_ptr, 
                          spi_data_out * local_spi_data_out_ptr)
{
    * local_spi_data_out_ptr->datatype_unsignedint = local_state_vars_ptr->wheelencR_count;
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}

/* -----------------------------------------------------------------------------
 * Function: state_open_grabber()
 * 
 * 
 * Opens the grabber arm entirely, and breaks when open.
 * 
 * INPUTS: none
 * 
 * OUTPUTS: none
 */
void state_open_grabber()
{
    
}

/* -----------------------------------------------------------------------------
 * Function: state_close_grabber()
 * 
 * 
 * Closes the grabber arm entirely, and breaks when fully closed.
 * 
 * INPUTS: none
 * 
 * OUTPUTS: none
 */    
void state_close_grabber()
{
    
}

/* -----------------------------------------------------------------------------
 * Function: state_read_grabber()
 * 
 * Reads the current state of the grabbers (open or closed)
 * 
 * INPUTS: none
 * 
 * OUTPUTS: none
 */       
void state_read_grabber()
{
    
}

/* -----------------------------------------------------------------------------
 *Function: state_read_comp(control_variables * local_state_vars_ptr, 
 *                          spi_data_out * local_spi_data_out_ptr);
 * 
 * Reads the current compass heading out to the PI as a SPI command.
 * 
 * INPUTS: local_state_vars_ptr, local_spi_data_out_ptr
 * 
 * OUTPUTS: none
 */
void state_read_comp(control_variables * local_state_vars_ptr, 
                     spi_data_out * local_spi_data_out_ptr)
{
    * local_spi_data_out_ptr->datatype_unsignedint = local_state_vars_ptr->compass_currentheading;
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}

/* -----------------------------------------------------------------------------
 * Functions to read the L,R,FRONT and CUBE photosensors back to the PI
 *
 */
void state_read_psns_L(control_variables * local_state_vars_ptr, 
                       spi_data_out * local_spi_data_out_ptr)
{
    * local_spi_data_out_ptr->datatype_unsignedint = local_state_vars_ptr->
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}
       
void state_read_psns_R(control_variables * local_state_vars_ptr, 
                       spi_data_out * local_spi_data_out_ptr)
{
    * local_spi_data_out_ptr->datatype_unsignedint = local_state_vars_ptr->
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}
      
void state_read_psnsfnt(control_variables * local_state_vars_ptr, 
                        spi_data_out * local_spi_data_out_ptr)
{
    * local_spi_data_out_ptr->datatype_unsignedint = local_state_vars_ptr->
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}
     
void state_read_psnscbe(control_variables * local_state_vars_ptr, 
                        spi_data_out * local_spi_data_out_ptr)
{
    * local_spi_data_out_ptr->datatype_unsignedint = local_state_vars_ptr->
    
    local_state_vars_ptr->general_break_condition = STATE_BREAK;
}

/* -----------------------------------------------------------------------------
 * Function: state_write_led(control_variables * local_state_vars_ptr,
 *                           spi_state_data * local_state_data_ptr);
 * 
 * Turns a led off/on
 * 
 * INPUTS: control_variables * local_state_vars_ptr,
           spi_state_data * local_state_data_ptr
 * 
 * OUTPUTS: none
 */
void state_write_led(control_variables * local_state_vars_ptr,
                     spi_state_data * local_state_data_ptr)
{
    led_state temp_led_state;
    temp_led_state = (led_state) local_state_data_ptr->state_data->value; // read value from spi transfer
    
    switch(temp_led_state)
            case ALL_OFF:
                led_TMR5_off_all();
                break;
            case BLUE_ON:
                led_const_blue_on();
                break;
            case BLUE_OFF:
                led_const_blue_off();
                break;
            case RED_ON:
                led_const_red_on();
                break;
            case RED_OFF:
                led_const_red_off();
                break;
            case GREEN_ON:
                led_const_grn_on();
                break;
            case GREEN_OFF:
                led_const_grn_off();
                break;
            case BLUE_FLASH:
                led_flash_blue_on(0xFFFF);
                break;
            case GREEN_FLASH:
                led_flash_grn_on(0xFFFF);
                break;
}

/* -----------------------------------------------------------------------------
 * Function: state_read_dip(control_variables * local_state_vars_ptr
 *                          spi_data_out * local_spi_data_out_ptr)
 * 
 * Reads the 4 dips switches, and sends the value read back to the pi.
 * 
 * INPUTS: control_variables * local_state_vars_ptr
           spi_data_out * local_spi_data_out_ptr
 * 
 * OUTPUTS: none
 */
void state_read_dip(control_variables * local_state_vars_ptr,
                    spi_data_out * local_spi_data_out_ptr)
{
    unsigned int temp_dipsw_data;
    unsigned int * temp_dipsw_data_ptr = &temp_dipsw_data;
    
    readDIP(temp_dipsw_data_ptr);   // read switches
    
    // write switch value to spi out data structure
    local_spi_data_out_ptr->datatype_unsignedint = * temp_dipsw_data_ptr;
}