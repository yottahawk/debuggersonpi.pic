/* 
 * File:   StateMachine.h
 * Author: Luke
 *
 * Created on 02 February 2016, 19:54
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "StateMachine.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

state_conditions_t state_conditions;
state_t Curr_State, Next_State, Prev_State;

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

//////////////////////////////////FUNCTIONS/////////////////////////////////////

//dummy defines
char POLL_TIMER_INT_FL = 1;

state_t get_curr_state() {
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
}

/* -----------------------------------------------------------------------------
 * Function: state_handler()
 * 
 * Top level function for state machine - a new state starts execution here.
 * REMEMBER ALL THE DATA STORED LOCALLY IS SPECIFIC TO THE CURRENT STATE OF OPERATION
 * 
 * Local copy of SPI_newstate arguments are created.
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
void state_handler() {
    // Create local copy of new_state arguments.
    // eg. copy arguments from global variables.
    
    // Create local struct for storage of any tracking data.
    control_variables local_state_vars;
    control_variables * local_state_vars_ptr = &local_state_vars;
    
    // Initialise members of struct (may create a function for this)
    local_state_vars.pid_ctrl_ptr = &(local_state_vars.Controller1); // Ptr to struct Controller1
    local_state_vars.psns_samples_ptr = &(local_state_vars.psns_samples);   // Ptr to array psns_samples
    
    // Create local struct for storage of any break conditions.
    break_conditions local_state_break_conditions;
    
    // Call state_setup function to initialise any modules necessary.
    
    
    while(1) // remain in this function until a new state is triggered
    {
        // wait for poll_TMR ISR to set flag
        while(!POLL_TIMER_INT_FL);
        POLL_TIMER_INT_FL = 0; // reset flag

        // branch to state-specific control algorithms
        switch_statecontrol(control_variables * local_state_vars_ptr);
        
        // Check for break conditions (intersection, collision, cube, distance, angle etc.)
        if (local_state_vars.general_break_condition = STATE_BREAK){return()};
        switch_statebreak(control_variables * local_state_vars_ptr);
    
        // Check for new_state available
    
    } // while(1)
}
    