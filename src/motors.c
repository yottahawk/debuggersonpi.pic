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
#include "i2c.h"
// #include "Encoder1Peripheral.c"
// #include "Encoder2Peripheral.c"

///////////////////////////////////TYPEDEFS/////////////////////////////////////

//typedef enum 
//{
//    FWD = 0,
//    REV 
//} motor_direction ;

///////////////////////////////////DEFINES//////////////////////////////////////

#define BAUD_RATE 79 // sets a i2c clock rate of 50 kHz
#define DIGIPOT_ADDRESS_WRITE 0b01011100 // 7 bit address of digipot + 0 for write
#define DIGIPOT_ADDRESS_READ 0b01011101 // 7 bit address of digipot + 1 for read


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

int  L_motor_SpeedGet() {}
int  R_motor_SpeedGet() {}

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
