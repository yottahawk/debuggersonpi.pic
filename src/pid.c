/*
 * File:   pid.c
 * Author: Harry
 *
 * Created on February 13, 2016, 6:06 PM
 */

/*
 * A PID controller is implemented using int data types. The precision gained by 
 * using float data types is not significant when compared to the increase in calculation 
 * time for this application.
 * 
 * All of the variables for the control system need to be defined in one location
 * to ensure the signs carry through correctly.
 * Eg. Does positive mean turn left or right, speed up or slow down, etc.
 * 
 * The process variable (pv) input and the control variable (cv) output need to
 * be considered in how an int will map to a real variable. 
 * 
 * The pv represents an estimate of the current heading of the robot. This is
 * created using sensor data from the LDR's and the compass. This may represent 
 * an angle of displacement to the desired heading, or an absolute angle.
 * 
 * The sv represents some change to the drive motors that will decrease the error 
 * in the pv. The robot will turn using skid steer, so somehow the relative 
 * velocities between the two wheels will be altered. However, it may make sense 
 * to keep the average velocity similar, and modulate the difference in speed 
 * between each side. This will prevent runaway.
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "pid.h"

#include "math.h" // 

/////////////////////////////////////DEFINES////////////////////////////////////

#define ProportionalGain 10;          // Proportional Gain
#define IntegralGain 10;          // Integral Gain

#define error_i_max 100;    // Max value for integral error (prevent integral wind up)

#define bound_max 50;      // Bound on max value of output 
#define bound_min 50;      // Bound on min value of output

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

typedef struct 
{
    int sp;       // Setpoint is input, goal or desired state.
    
    int max;            // Set max bound on output
    int min;            // Set min bound on output
    
    int e;          // Error on current time step.
    int p_e[2];                  // Saved error of previous 2 time steps
    int i_sum;         // Sum of all previous errors
    
    int kp;             // Proportional Gain
    int ki;             // Integral Gain
    
} pid_ctrl;

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

pid_ctrl Controller1;               
pid_ctrl * pid_ctrl_ptr = &Controller1; // Instantiate a pointer to the struct Controller1

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

void pid_init(pid_ctrl * ptr,       // Ptr to the pid controller struct
              int max,            
              int min)
{
    /*
     * Initialises the memebers of the pid controller struct. This must also be 
     * called to reset the values back to their default values. Whenever a new 
     * tracking state is to begin, the controller must be reset.
     */
    
    // Now initialise the struct "controller1"
    ptr->sp = 0;
    
    ptr->max = bound_max;
    ptr->min = bound_min;
    
    ptr->e = 0;
    ptr->p_e[2] = 0;
    ptr->i_sum = 0;
    
    ptr->kp = ProportionalGain;
    ptr->ki = IntegralGain;
}

int pid_update(int sp,               // setpoint
               int pv,               // process variable - estimate of plant output as measured by sensors
               pid_ctrl * ptr)       // ptr to controller struct in use
{
    /*
     *  This method creates a new control variable based on the variables passed to it.
     *  The process variable is created by an estimation process using any relevant sensor data.
     *  The 
     */
    
    int cv;     // Control variable - the output of the controller into the plant
    int temp_i_sum;  // Accumulated error - this may not update if the controller has hit the high or low bounds.
    
    ptr->p_e[2] = ptr->p_e[1];    // Move previous error down array
    ptr->e = sp - pv;             // Calculate current error.
    ptr->p_e[1] = ptr->e;                 // Copy current error to top of array.
    
    temp_i_sum = ptr->i_sum + ptr->e ;    // update accumulated error
    
    // Calculate new control variable
    cv = (ptr->kp * ptr->e) + (ptr->ki * ptr->i_sum);
    // =       kp * e       +       ki * integral(e)
    
    // Now ensure the cv stays within the bounds.
    if ((cv < ptr->max) && (cv > ptr->min))
    { ptr->i_sum = temp_i_sum; }        // Only increase i_sum if cv within bounds
    else if (cv > ptr->max)
    { cv = ptr->max; }    // If greater the max then set equal to max
    else if (cv < ptr->min)
    { cv = ptr->min; }    // If less than min then set equal to min
    
    return cv;
}

