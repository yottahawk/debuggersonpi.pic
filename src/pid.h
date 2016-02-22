/* 
 * File: pid.h
 * Author: Harry Callahan
 * 
 * Comments: Methods for running a discrete time PID control system.
 *  
 * This system will control the robot heading, allowing it to track a line 
 * on which it is traveling. It will use the reflective line tracking sensors, 
 * or the digital compass, or both as input variables. 
 * 
 * The output will be used to control the speed of each wheel independently, allowing
 * turning using the skid steer method.
 * 
 * Revision history: 
 */

#ifndef debuggersonpi_pic_pid_h
#define debuggersonpi_pic_pid_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

typedef struct 
{
    int sp;             // Setpoint is input, goal or desired state.
    int cv;             // Control variable output of PID
    
    int max;            // Set max bound on output
    int min;            // Set min bound on output
    
    int e;              // Error on current time step.
    int p_e[2];         // Saved error of previous 2 time steps
    int i_sum;          // Sum of all previous errors
    
    int kp;             // Proportional Gain
    int ki;             // Integral Gain
    
} pid_ctrl;

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

#endif //debuggersonpi_pic_pid_h