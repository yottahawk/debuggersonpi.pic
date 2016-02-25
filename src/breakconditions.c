/*
 * File:   breakconditions.c
 * Author: Harry
 * 
 * Created on February 10, 2016, 8:31 PM
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "breakconditions.h"
#include "datatypes.h"

/////////////////////////////////////DEFINES////////////////////////////////////

#define singlemeasurebreakangle
// #define recentmeasurebreakangle 

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

void bc_counts_LorR(control_variables * local_state_vars_ptr)
{
// if both wheels reached desired count, trigger break condition
    if (local_state_vars_ptr->wheelencL_count > local_state_vars_ptr->wheelencL_limit ||
        local_state_vars_ptr->wheelencR_count > local_state_vars_ptr->wheelencR_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    };
}

void bc_counts_LandR(control_variables * local_state_vars_ptr)
{
// if both wheels reached desired count, trigger break condition
    if (local_state_vars_ptr->wheelencL_count > local_state_vars_ptr->wheelencL_limit &&
        local_state_vars_ptr->wheelencR_count > local_state_vars_ptr->wheelencR_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    };
}

void bc_counts_L(control_variables * local_state_vars_ptr)
{
    // if left wheel reaches desired count, trigger break condition
    if (local_state_vars_ptr->wheelencL_count > local_state_vars_ptr->wheelencL_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    }; 
}

void bc_counts_R(control_variables * local_state_vars_ptr)
{
    // if left wheel reaches desired count, trigger break condition
    if (local_state_vars_ptr->wheelencR_count > local_state_vars_ptr->wheelencR_limit)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK; 
        return;
    }; 
}

void angle_smallerror(control_variables * local_state_vars_ptr)
{
    // if the error in angle is small, trigger break condition
    
    // do we want some error tracking? or just trigger on a single measurement
    // use define statements to choose which function
    // tracking -> define a small array, and check every value against threshold.
   
#ifdef singlemeasurebreakangle
    // single measurement
    if(* local_state_vars_ptr->Controller1.p_e_ptr <= 1)        // check most recent error
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK;
    }
#endif 
    
#ifdef recentmeasurebreakangle 
    // track recent measurements
    if(* (local_state_vars_ptr->Controller1.p_e_ptr)        <= 1 &&
         (local_state_vars_ptr->Controller1.p_e_ptr + 1)    <= 1 && 
         (local_state_vars_ptr->Controller1.p_e_ptr + 2)    <= 1)
    {
        local_state_vars_ptr->general_break_condition = STATE_BREAK;
    }
#endif
}

/* -----------------------------------------------------------------------------
 *Function: detectIntersection()
 * 
 * Uses the digital photosensors(L,R,Front) to detect the junction, and identify which
 * junction that is.
 * 
 * This algorithm should be resistant to noise, as there are transitions on the L,R sensors
 * that arent that start of junction. (crossing between rooms)
 * 
 * If a junction is detected, it should record which one, and set a flag to ensure the
 * next state transition is to one which moves the robot to the centre of the room.
 * This will probably be an encoders_fwd state, moving the remaining distance forward.
 * 
 * This algorithm should only break when the robot has detected the junction, and it
 * should know where abouts in a room this is every time.
 * 
 * INPUTS: local_state_vars -> array of L,R,Front samples
 *         
 * OUTPUTS: none (sets detected junction flag)
 */
void detectIntersection(control_variables * local_state_vars_ptr)
{
    
}
