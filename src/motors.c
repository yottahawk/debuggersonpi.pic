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

void L_motor_counts_constSpeed(int delta_count, motor_direction_type direction, int speed)
{
    /*
     * Drive the left motor a defined number of counts, at a defined
     * constant speed.
     * 
     */
    
    
}

void R_motor_counts_constSpeed(int delta_count, motor_direction_type direction, int speed)
{
    /*
     * Drive the left motor a defined number of counts, at a defined
     * constant speed.
     * 
     */
    
    
}

void L_motor_constSpeed(motor_direction_type direction, int speed)
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

void R_motor_constSpeed(motor_direction_type direction, int speed)
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

void SetFeedbackRes(int resistance)
{
    char x;
    
    // See data sheet for command byte structure
    // = Memory Address & Command Operation & two data bits D8 and D9 (only D8 is used)
    char command_byte = 0b00000000;     // Write data to wiper0 register
    char wiper0_byte = resistance;      // Set value of wiper position
    
    i2c_init(BAUD_RATE);
    i2c_start();
    
    x = send_i2c_byte(DIGIPOT_ADDRESS_WRITE);     // Defined at top of page.
    if (x == 1){return;}
    x = send_i2c_byte(command_byte);
    if (x == 1){return;}
    x = send_i2c_byte((char) wiper0_byte);  // Explicit type conversion here
    if (x == 1){return;}
    
    i2c_resetbus();
}

void SetMotorVoltage(int voltage)
{
    
}

void initDigiPot()
{
    char x;
    
    // See data sheet for command byte structure
    // = Memory Address & Command Operation & two data bits D8 and D9 (only D8 is used)
    char command_byte = 0b01000000;     // Write data to TCON register
    char TCON_byte = 0b00001011;       // Connects P0B and P0W to resistor network
    
    i2c_init(BAUD_RATE);
    i2c_start();
    
    x = send_i2c_byte(DIGIPOT_ADDRESS_WRITE);     // Defined at top of page.
    if (x == 1){return;}
    x = send_i2c_byte(command_byte);
    if (x == 1){return;}
    x = send_i2c_byte(TCON_byte);
    if (x == 1){return;}
    
    i2c_resetbus();
}

void IncrementWiper()
{
    char x;
    
    // See data sheet for command byte structure
    // = Memory Address & Command Operation & two data bits D8 and D9 (only D8 is used)
    char command_byte = 0b00000100;     // Increment wiper0 register
    // char wiper0_byte = resistance;      // Set value of wiper position
    
    i2c_init(BAUD_RATE);
    i2c_start();
    
    x = send_i2c_byte(DIGIPOT_ADDRESS_WRITE);     // Defined at top of page.
    if (x == 1){return;}
    x = send_i2c_byte(command_byte);
    if (x == 1){return;}
    
    // No data byte for increment command
    
    i2c_resetbus();
}
