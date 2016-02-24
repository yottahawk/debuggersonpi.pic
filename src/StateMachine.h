/* 
 * File:   StateMachine.h
 * Author: Luke
 *
 * Created on 02 February 2016, 19:54
 */

#ifndef debuggersonpi_pic_statemachine_h
#define debuggersonpi_pic_statemachine_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"
#include "datatypes.h"

#include "states.h"
#include "states_setup.h"

#include "spi.h"
#include "pid.h"
#include "wheelEncoders.h"
#include "compass.h"
#include "timers.h"
#include "interrupts.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

state_t get_curr_state();
state_t get_next_state();
state_t get_prev_state();
state_conditions_t get_conditions();

void set_curr_state(state_t state);
void set_next_state(state_t state);
void set_prev_state(state_t state);
void set_conditions(state_conditions_t conditions);

void state_handler(spi_state_data * newstate_ptr);

void atomic_sensorcopy(control_variables * local_state_vars_ptr);

void copyencdr_tolocal(control_variables * local_state_vars_ptr);
void copypsns_tolocal(control_variables * local_state_vars_ptr);
void copycompass_tolocal(control_variables * local_state_vars_ptr);

void switch_statebreak(control_variables * local_state_vars_ptr,
                          spi_state_data * local_currentstate_data_ptr);

void pid_updatemotors_fwd(control_variables * local_state_vars_ptr);

void pid_updatemotors_rev(control_variables * local_state_vars_ptr);

void pid_updatemotors_turn(control_variables * local_state_vars_ptr);

#endif //debuggersonpi_pic_statemachine_h





