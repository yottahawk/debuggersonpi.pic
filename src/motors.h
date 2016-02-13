/* 
 * File: motors.h 
 * Author: Harry
 * Comments: Methods for driving the motors.
 * Revision history: 
 */

///////////////////////////////////TYPEDEFS/////////////////////////////////////

typedef enum 
{
    FWD = 0,
    REV 
} motor_direction ;

/////////////////////////////////FUNCTIONS//////////////////////////////////////

void enableMotorPSU();
void disableMotorPSU();


void L_motor_counts_constSpeed(int delta_count, motor_direction direction, int speed);
void R_motor_counts_constSpeed(int delta_count, motor_direction direction, int speed);

void L_motor_constSpeed(motor_direction direction, int speed);
void R_motor_constSpeed(motor_direction direction, int speed);

void SetFeedbackRes(int resistance);

void SetMotorVoltage(int voltage);

void initDigiPot();

void IncrementWiper();