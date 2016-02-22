/* 
 * File:   compass.h
 * Author: Harry
 * 
 * Comments:
 *
 * Created on February 13, 2016, 11:21 PM
 */

#ifndef debuggersonpi_pic_compass_h
#define debuggersonpi_pic_compass_h

//////////////////////////////////////INCLUDES//////////////////////////////////

#include "xc.h"

//#include "I2C1.h"
//#include "I2C2.h"


//////////////////////////////////////DEFINES///////////////////////////////////

// Only define one or the other!
// #define I2C1_enable
//#define I2C2_enable

#define BAUD_RATE 79                   // 79 = i2c clock of 50kHz

#define HMC5883L_ADDR            0x3C 

#define SLAVE_READ_FROM          0x01
#define SLAVE_WRITE_TO           0x00
                            
#define Config_Reg_A             0x00 
#define Config_Reg_B             0x01 
#define Mode_Reg                 0x02 
#define X_MSB_Reg                0x03 
#define X_LSB_Reg                0x04 
#define Z_MSB_Reg                0x05 
#define Z_LSB_Reg                0x06 
#define Y_MSB_Reg                0x07 
#define Y_LSB_Reg                0x08 
#define Status_Reg               0x09 
#define ID_Reg_A                 0x0A              
#define ID_Reg_B                 0x0B 
#define ID_Reg_C                 0x0C

// Config register data bytes
#define Config_A_Data            0x70  // Normal measurement mode, ODR = 15Hz, 8 averaged samples
#define Config_B_Data            0x20  // +-1.3 Ga
#define Mode_Data_Single         0x01  // Single measurment mode
#define Mode_Data_Continuous     0x00  // Continuous measurment mode

// Angle between magnetic north and geographic north
// Magnetic declination is 1.37 degrees WEST
#define declination_angle        // For Bristol    

////////////////////////////////TYPEDEFS,ENUMS,STRUCTS//////////////////////////

typedef enum 
{ 
    GaussA = 0,     // 0.88
    GaussB,         // 1.3
    GaussC,         // 1.9
    GaussD,         // 2.5
    GaussE,         // 4.0
    GaussF,         // 4.7
    GaussG,         // 5.6
    GaussH          // 8.1
} set_gauss_scale;

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

extern int currentheading;          // Value of current heading
extern int prevheadings[100];       // Buffer containing previous headings

///////////////////////////////FUNCTION DECLARATIONS////////////////////////////

void initCompass(); // Init I2c comms, 
void selfTestCompass(); // Run self test and verify pass

void scaleAxis(); // Scale the output of each axis.
void setGain(set_gauss_scale value);     // Use an enum to set the gauss scale

int createIntFromChars(unsigned char MSB, unsigned char LSB); // Create int from two chars
unsigned char readCompass(unsigned char reg); // Read the value of a certain register
void writeCompass(unsigned char reg_address, unsigned char value); // Writes to a register

void readCompassData();     // Reads the relevant data to a buffer
void calculateHeading();    // Takes the buffer data and calculates a heading

unsigned char periph_readCompass(unsigned char reg_address);
void periph_writeCompass(unsigned char reg_address, unsigned char value);

////////////////////////////////////////////////////////////////////////////////
#endif //debuggersonpi_pic_compass_h
