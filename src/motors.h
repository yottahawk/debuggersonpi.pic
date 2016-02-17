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

#include "oc.h"
#include "timers.h"
#include "i2c.h"
#include "wheelEncoders.h"

//////////////////////////////////////DEFINES///////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////TYPEDEFS,ENUMS,STRUCTS//////////////////////////

// This enum is used as an argument to a function, but is never instantiated. There
// is no need to initialise a state of FWD or REV.
typedef enum 
{ 
    FWD = 0,
    REV
} motor_direction_type;

///////////////////////////////FUNCTION DECLARATIONS////////////////////////////

void enableMotorPSU();
void disableMotorPSU();


void L_motor_counts_constSpeed(int delta_count, motor_direction_type direction, unsigned int speed);
void R_motor_counts_constSpeed(int delta_count, motor_direction_type direction, unsigned int speed);

void L_motor_constSpeed(motor_direction_type direction, unsigned int speed);
void R_motor_constSpeed(motor_direction_type direction, unsigned int speed);

int  L_motor_SpeedGet();
int  R_motor_SpeedGet();

void SetFeedbackRes(int resistance);

void SetMotorVoltage(int voltage);

void initDigiPot();

void IncrementWiper();

////////////////////////////////////////////////////////////////////////////////
#endif //debuggersonpi_pic_motors_h

