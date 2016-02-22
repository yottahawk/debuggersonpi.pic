/* 
 * File: motors.h 
 * Author: Harry
 * Comments: Methods for driving the motors.
 * Revision history: 
 */

#ifndef debuggersonpi_pic_motors_h
#define debuggersonpi_pic_motors_h

//////////////////////////////////////INCLUDES//////////////////////////////////

#include "xc.h"

#include "StateMachine.h"
#include "oc.h"
#include "timers.h"
//#include "I2C1.h"
#include "wheelEncoders.h"

//////////////////////////////////////DEFINES///////////////////////////////////

#define deg90counts_L 27;       // no of counts for 90 degrees or robot rotation
#define deg90counts_R 27;       // no of counts for 90 degrees or robot rotation

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////TYPEDEFS,ENUMS,STRUCTS//////////////////////////

// This enum is used as an argument to a function, but is never instantiated. 
typedef enum 
{ 
    FWD = 0,
    REV
} motor_direction_type;

///////////////////////////////FUNCTION DECLARATIONS////////////////////////////

unsigned int acceleration_control(unsigned int requested_speed, control_variables * local_state_vars_ptr);
void reset_motortracking();
void enableMotorPSU();
void disableMotorPSU();

void L_motor_constSpeed(motor_direction_type direction, unsigned int speed);
void R_motor_constSpeed(motor_direction_type direction, unsigned int speed);

void L_motor_acceltoconstSpeed(control_variables * local_state_vars_ptr, motor_direction_type direction, unsigned int speed);
void R_motor_acceltoconstSpeed(control_variables * local_state_vars_ptr, motor_direction_type direction, unsigned int speed);

void motors_dual_constspeed(motor_direction_type direction, unsigned int speed);

// access methods to motor_tracking_struct
int L_motor_SpeedGet(); 
int R_motor_SpeedGet(); 
motor_direction_type L_motor_DirectionGet();
motor_direction_type R_motor_DirectionGet();

////////////////////////////////////////////////////////////////////////////////
#endif //debuggersonpi_pic_motors_h

