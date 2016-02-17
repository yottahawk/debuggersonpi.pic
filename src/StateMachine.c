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

//Function to run through states
void StateMachine() {
    
    //First wait until the interrupt flag for polling interrupt is high
    //once detected, reset to low
    while(!POLL_TIMER_INT_FL);
    POLL_TIMER_INT_FL = 0;
    
    //execute a different function based on state
    switch (Curr_State) {
        case OL_FORWARD: ol_forward();
        default: ol_stopped();
    }
}