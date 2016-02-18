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

#define BAUD_RATE 79 // sets a i2c clock rate of 50 kHz
#define DIGIPOT_ADDRESS_WRITE 0b01011100 // 7 bit address of digipot + 0 for write
#define DIGIPOT_ADDRESS_READ 0b01011101 // 7 bit address of digipot + 1 for read

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

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
}

void L_motor_counts_constSpeed(int delta_count, motor_direction_type direction, unsigned int speed)
{
    /*
     * Drive the left motor a defined number of counts, at a defined
     * constant speed.
     * 
     */
    
    
}

void R_motor_counts_constSpeed(int delta_count, motor_direction_type direction, unsigned int speed)
{
    /*
     * Drive the left motor a defined number of counts, at a defined
     * constant speed.
     * 
     */
    
    
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
    
}

//Note: Int has negativity,and can therefore express direction
int  L_motor_SpeedGet() {
    return 0;
}
int  R_motor_SpeedGet() {
    return 0;
}



