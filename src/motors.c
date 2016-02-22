/*
 * File:   motors.c
 * Author: Harry
 *
 * Drives the motors forward and backwards.
 * 
 * Created on February 7, 2016, 10:15 PM
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "motors.h"

/////////////////////////////////////DEFINES////////////////////////////////////

#define compensation_factor 1.00       // compensate for unbalanced motor speeds

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

/*
 * This data structure holds the current values of variables relating to the 
 * current status of the motors. They are updated each time a function call is 
 * made that changes the state of the motors in any way. 
 * This allows the current variables to be easily read back.
 */
typedef struct 
{
    int motorPSUenabled;
    
    motor_direction_type motorL_direction;
    motor_direction_type motorR_direction;
    unsigned int motorL_speed;
    unsigned int motorR_speed;
    
    unsigned int acceleration_track;
  
} motors_tracking;

motors_tracking motor_tracking_struct = {0};      // define tracking struct within entire file.   
motors_tracking empty_struct = {0};               // used for reset

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

/* -----------------------------------------------------------------------------
 * Function: acceleration_control(unsigned int requested_speed)
 * 
 * Implement a rudimentary acceleration controller using the update_counter variable.
 * The motor speed is allowed to increase as the number of update loops increases.
 */
unsigned int acceleration_control(unsigned int requested_speed, control_variables * local_state_vars_ptr)
{
    if (requested_speed <= local_state_vars_ptr->update_counter)
    {
        return requested_speed;
    }
    else 
    {
        return local_state_vars.update_counter;     // speed can never be greater than number of update cycles.
    }
}

/* -----------------------------------------------------------------------------
 * Function: reset_motortracking()
 * 
 * Resets the motor_tracking data structure. This should occur whenever a 
 * change of state occurs.
 */
void reset_motortracking()
{
    motor_tracking_struct = empty_struct;       // reset struct to defaults
}

void enableMotorPSU()
{
    /*
     * Sets the enable line high, starting the power supply for the two drive motors.
     * This does not need to be disabled when the motors are not running.
     * 
     * The motors will still run if the supply is off, except they will be driven 
     * from the battery supply voltage. This is not an ideal load case for the batteries.
     */
    LATBbits.LATB14 = 1;    // enable motor power supply
    motor_tracking_struct.motorPSUenabled = 1;
}

void disableMotorPSU()
{
    /*
     * Sets the enable line low, disabling the power supply for the two drive motors.
     * 
     * The motors will still run if the supply is off, except they will be driven 
     * from the battery supply voltage. This is not an ideal load case for the batteries.
     */
    
    LATBbits.LATB14 = 0;    // disable motor power supply
    motor_tracking_struct.motorPSUenabled = 0;
}

void L_motor_constSpeed(motor_direction_type direction, unsigned int speed)
{
    /*
     * Drive the left motor at a defined constant speed.
     * 
     */
    
    if (direction == FWD)         // Forward
    {
        OC5init();
        OC5dutyset(speed);
    }
    else if (direction == REV)    // Backwards
    {
        OC4init();
        OC4dutyset(speed);
    }
    
    motor_tracking_struct.motorL_speed = speed;     // track current speed
    motor_tracking_struct.motorL_direction = direction;
}

void R_motor_constSpeed(motor_direction_type direction, unsigned int speed)
{
    /*
     * Drive the left motor at a defined constant speed.
     * 
     */
    
    if (direction == FWD)         // Forward
    {
        OC2init();
        OC2dutyset(speed);
    }
    else if (direction == REV)    // Backwards
    {
        OC3init();
        OC3dutyset(speed);
    }   
    
    motor_tracking_struct.motorR_speed = speed;     // track current speed
    motor_tracking_struct.motorR_direction = direction; 
}

/* -----------------------------------------------------------------------------
 * Function: L_motor_acceltoconstSpeed(motor_direction_type direction, unsigned int speed)
 * 
 * Motor accelerates to the given speed. The acceleration is controlled by the 
 * current update_counter value.
 * 
 * INPUTS: motor direction, and desired speed.
 * 
 * OUTPUTS: none
 */
void L_motor_acceltoconstSpeed(control_variables * local_state_vars_ptr, motor_direction_type direction, unsigned int speed)
{
    unsigned int new_speed = acceleration_control(speed,local_state_vars_ptr);
    
    if (direction == FWD)         // Forward
    {
        OC5init();
        OC5dutyset(new_speed);
    }
    else if (direction == REV)    // Backwards
    {
        OC4init();
        OC4dutyset(new_speed);
    }
    
    motor_tracking_struct.motorL_speed = speed;     // track current speed
    motor_tracking_struct.motorL_direction = direction;
}

/* -----------------------------------------------------------------------------
 * Function: R_motor_acceltoconstSpeed(motor_direction_type direction, unsigned int speed)
 * 
 * Motor accelerates to the given speed. The acceleration is controlled by the 
 * current update_counter value.
 * 
 * INPUTS: motor direction, and desired speed.
 * 
 * OUTPUTS: none
 */
void R_motor_acceltoconstSpeed(control_variables * local_state_vars_ptr, motor_direction_type direction, unsigned int speed)
{
    unsigned int new_speed = acceleration_control(speed,local_state_vars_ptr);
    
    if (direction == FWD)         // Forward
    {
        OC2init();
        OC2dutyset(new_speed);
    }
    else if (direction == REV)    // Backwards
    {
        OC3init();
        OC3dutyset(new_speed);
    }   
    
    motor_tracking_struct.motorR_speed = speed;     // track current speed
    motor_tracking_struct.motorR_direction = direction; 
}



int L_motor_SpeedGet() 
{
    return motor_tracking_struct.motorL_speed;
}
int R_motor_SpeedGet() 
{
    return motor_tracking_struct.motorR_speed;
}
motor_direction_type L_motor_DirectionGet()
{
    return motor_tracking_struct.motorL_direction;
}
motor_direction_type R_motor_DirectionGet()
{
    return motor_tracking_struct.motorR_direction;
}

/* -----------------------------------------------------------------------------
 * Function: motors_dual_constspeed()
 * 
 * Drives both motors at the given speed, both in the given direction.
 * A compensating factor is used to try and equalise the imbalance betweeen motors.
 * 
 * This function should only be used for open-loop control.
 * 
 * INPUTS: direction and speed, compensation factor
 * 
 * OUTPUTS: none
 */
void motors_dual_constspeed(motor_direction_type direction, unsigned int speed)
{
    // First apply compensation between two motors. 
    // Compensation factor is defined in the preprocessor.
    unsigned int temp_L_speed = speed;
    unsigned int temp_R_speed = speed;
    
    float comp_factor;
    comp_factor = compensation_factor;  // use prepreocessor define
    
    temp_L_speed = (unsigned int) temp_L_speed * comp_factor; // apply compensation
    
    L_motor_constSpeed(motor_direction_type direction, unsigned int temp_L_speed);
    R_motor_constSpeed(motor_direction_type direction, unsigned int temp_R_speed);
}
