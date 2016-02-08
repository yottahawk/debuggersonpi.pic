/*
 * File:   motors.c
 * Author: Harry
 *
 * Drives the motors forward and backwards.
 * 
 * Created on February 7, 2016, 10:15 PM
 */

///////////////////////////////////INCLUDES/////////////////////////////////////

#include "xc.h"
#include "motors.h"

#include "oc.h"
#include "timers.h"
// #include "Encoder1Peripheral.c"
// #include "Encoder2Peripheral.c"

///////////////////////////////////TYPEDEFS/////////////////////////////////////

//typedef enum 
//{
//    FWD = 0,
//    REV 
//} motor_direction ;


///////////////////////////////////FUNCTIONS////////////////////////////////////

void L_motor_counts_constSpeed(int delta_count, motor_direction direction, int speed)
{
    /*
     * Drive the left motor a defined number of counts, at a defined
     * constant speed.
     * 
     */
    
    
}

void R_motor_counts_constSpeed(int delta_count, motor_direction direction, int speed)
{
    /*
     * Drive the left motor a defined number of counts, at a defined
     * constant speed.
     * 
     */
    
    
}

void L_motor_constSpeed(motor_direction direction, int speed)
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
    
}

void R_motor_constSpeed(motor_direction direction, int speed)
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
    
}