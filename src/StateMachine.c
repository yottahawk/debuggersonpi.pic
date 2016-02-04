/* 
 * File:   StateMachine.h
 * Author: Luke
 *
 * Created on 02 February 2016, 19:54
 */

#include "StateMachine.h"
#include "OpenLoop.h"

//dummy defines
char POLL_TIMER_INT_FL = 1;

//Function to run through states
void StateMachine() {
    
    //First wait until the interrupt flag for polling interrupt is high
    //once detected, reset to low
    while(!POLL_TIMER_INT_FL);
    POLL_TIMER_INT_FL = 0;
    
    //execute a different function based on state
    switch (curr_state) {
        case OL_FORWARD: ol_forward();
        default: ol_stopped();
    }
}