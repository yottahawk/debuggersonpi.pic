/* 
 * File:   states.h
 * Author: Harry
 * 
 * Comments: This module holds the unique execution path for each state.
 * 
 *
 * Created on February 20, 2016, 10:05 PM
 */

#ifndef debuggersonpi_pic_states_h
#define debuggersonpi_pic_states_h

//////////////////////////////////////INCLUDES//////////////////////////////////

#include "xc.h"

#include "StateMachine.h"
#include "datatypes.h"
#include "motors.h"
#include "linefollow.h"
#include "led.h"
#include "grabber.h"
#include "pid.h"
#include "indicators_switches.h"

//////////////////////////////////////DEFINES///////////////////////////////////

////////////////////////////////TYPEDEFS,ENUMS,STRUCTS//////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

///////////////////////////////FUNCTION DECLARATIONS////////////////////////////

void switch_statecontrol(control_variables * local_state_vars_ptr,
                         spi_state_data * local_state_data_ptr,
                         spi_data_out * local_spi_data_out_ptr);

void state_stopped();

// MOVEMENT STATES //

void state_ol_forward(control_variables * local_state_vars_ptr);

void state_ecdr_left(control_variables * local_state_vars_ptr);

void state_ecdr_right(control_variables * local_state_vars_ptr);

void state_ol_reverse(control_variables * local_state_vars_ptr);

void state_ecdr_rev_left(control_variables * local_state_vars_ptr);

void state_ecdr_rev_right(control_variables * local_state_vars_ptr);

void state_comp_forward(control_variables * local_state_vars_ptr);

void state_comp_turn(control_variables * local_state_vars_ptr);

void state_comp_reverse(control_variables * local_state_vars_ptr);

void state_comp_rev_left(control_variables * local_state_vars_ptr);

void state_comp_rev_right(control_variables * local_state_vars_ptr);

void state_ecdr_forward(control_variables * local_state_vars_ptr);

void state_ecdr_reverse(control_variables * local_state_vars_ptr);

void state_psns_forward(control_variables * local_state_vars_ptr);

// DIRECT ACCESS STATES //
//
//void state_write_motor_left_fwd(control_variables * local_state_vars_ptr,
//                                spi_state_data * local_state_data_ptr);
//
//void state_write_motor_left_rev(control_variables * local_state_vars_ptr,
//                                spi_state_data * local_state_data_ptr);
//
//void state_write_motor_right_fwd(control_variables * local_state_vars_ptr,
//                                spi_state_data * local_state_data_ptr);
//
//void state_write_motor_right_rev(control_variables * local_state_vars_ptr,
//                                spi_state_data * local_state_data_ptr);
//
//void state_read_ecdr1_sum(control_variables * local_state_vars_ptr, 
//                          spi_data_out * local_spi_data_out_ptr);
//
//void state_read_ecdr2_sum(control_variables * local_state_vars_ptr, 
//                          spi_data_out * local_spi_data_out_ptr);
//
//void state_open_grabber();
//   
//void state_close_grabber();
//     
//void state_read_grabber();
//
//void state_read_comp(control_variables * local_state_vars_ptr, 
//                     spi_data_out * local_spi_data_out_ptr);
//
//void state_read_psns_L(control_variables * local_state_vars_ptr, 
//                       spi_data_out * local_spi_data_out_ptr);
//
//       
//void state_read_psns_R(control_variables * local_state_vars_ptr, 
//                       spi_data_out * local_spi_data_out_ptr);
//
//void state_read_psnsfnt(control_variables * local_state_vars_ptr, 
//                        spi_data_out * local_spi_data_out_ptr);
//
//void state_read_psnscbe(control_variables * local_state_vars_ptr, 
//                        spi_data_out * local_spi_data_out_ptr);
//
//void state_write_led(control_variables * local_state_vars_ptr,
//                     spi_state_data * local_state_data_ptr);
//
//void state_read_dip(control_variables * local_state_vars_ptr,
//                    spi_data_out * local_spi_data_out_ptr);

////////////////////////////////////////////////////////////////////////////////
#endif //debuggersonpi_pic_states_h
