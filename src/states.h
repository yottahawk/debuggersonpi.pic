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

void switch_statesetup(control_variables * local_state_vars_ptr,
                       spi_state_data * local_currentstate_data_ptr);

// Default State - All SPI comms occurs within this state.
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

void state_psns_forward_junctiondetect(control_variables * local_state_vars_ptr);

// STATE SETUPS //

void setup_state_ol_forward(spi_state_data * local_currentstate_data_ptr,
                            control_variables * local_state_vars_ptr);

void setup_state_ecdr_left(spi_state_data * local_currentstate_data_ptr,
                           control_variables * local_state_vars_ptr);

void setup_state_ecdr_right(spi_state_data * local_currentstate_data_ptr,
                            control_variables * local_state_vars_ptr);

void setup_state_ol_reverse(spi_state_data * local_currentstate_data_ptr,
                            control_variables * local_state_vars_ptr);

void setup_state_ecdr_rev_left(spi_state_data * local_currentstate_data_ptr,
                               control_variables * local_state_vars_ptr);

void setup_state_ecdr_rev_right(spi_state_data * local_currentstate_data_ptr,
                                control_variables * local_state_vars_ptr);

void setup_state_comp_forward(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr);

void setup_state_comp_turn(spi_state_data * local_currentstate_data_ptr,
                           control_variables * local_state_vars_ptr);

void setup_state_comp_reverse(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr);

void setup_state_comp_rev_left(spi_state_data * local_currentstate_data_ptr,
                               control_variables * local_state_vars_ptr);

void setup_state_comp_rev_right(spi_state_data * local_currentstate_data_ptr,
                                control_variables * local_state_vars_ptr);

void setup_state_ecdr_forward(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr);

void setup_state_ecdr_reverse(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr);

void setup_state_psns_forward(spi_state_data * local_currentstate_data_ptr,
                              control_variables * local_state_vars_ptr);

void setup_state_psns_forward_junctiondetect(spi_state_data * local_currentstate_data_ptr,
                                             control_variables * local_state_vars_ptr);

////////////////////////////////////////////////////////////////////////////////
#endif //debuggersonpi_pic_states_h
