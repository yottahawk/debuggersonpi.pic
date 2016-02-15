/* 
 * File:   compass.c
 * Author: Harry
 *
 * Created on February 13, 2016, 11:21 PM
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "compass.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

// Externals
int currentheading;             // Value of current heading
int prevheadings[100];          // Buffer containing previous headings

// Internals
int X_axis;
int Y_axis;
int Z_axis;

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

/* 
 * Initializes the compass over an i2c comms channel. 
 * The comms channel is opened within the init method.
 * The HMC5883L is set up as desired for the given application.
 */
void initCompass()
{
    i2c_init(BAUD_RATE); 
     
    writeCompass(Config_Reg_A, Config_A_Data); 
    writeCompass(Config_Reg_B, Config_B_Data); 
    writeCompass(Mode_Reg, Mode_Data);  
    // setGain(GaussB);
}

void selfTestCompass(); // Run self test and verify pass

void scaleAxis(); // Scale the output of each axis.
void setGain(set_gauss_scale value);     // Use an enum to set the gauss scale

int createIntFromChars(unsigned char HB, unsigned char LB)
{
    // Create int from two chars
    
    int val = 0; 
                               
    val = HB; 
    val <<= 8;                          
    val |= LB;          
    return val;    
}; 

unsigned char readCompass(unsigned char reg_address)
{
    // Read the value of a certain register
    unsigned char val; 
    
    i2c_start();
    send_i2c_byte(HMC5883L_ADDR | SLAVE_WRITE_TO);
    send_i2c_byte(reg_address);

    i2c_repeatstart();
    
    send_i2c_byte(HMC5883L_ADDR | SLAVE_READ_FROM);
    val = i2c_read_ack();
    
    i2c_resetbus();
    
    return val;
} 

void writeCompass(unsigned char reg_address, unsigned char value)
{
    // Writes to a register
    i2c_init(BAUD_RATE);
    
    i2c_start();
    
    send_i2c_byte(HMC5883L_ADDR | SLAVE_WRITE_TO);
    send_i2c_byte(reg_address);
    send_i2c_byte(value);
    
    i2c_resetbus();
}

void readCompassData()
{
    // Reads the relevant data to a buffer
    
    unsigned char lsb_x = 0; 
    unsigned char msb_x = 0; 
    unsigned char lsb_y = 0; 
    unsigned char msb_y = 0;
    unsigned char lsb_z = 0; 
    unsigned char msb_z = 0;

    i2c_start(); 
    
    send_i2c_byte(HMC5883L_ADDR | SLAVE_WRITE_TO);        // Write    
    send_i2c_byte(X_MSB_Reg);  
    
    i2c_repeatstart();
    
    send_i2c_byte(HMC5883L_ADDR | SLAVE_READ_FROM);   // Read
    msb_x = i2c_read_ack(); 
    lsb_x = i2c_read_ack(); 
    msb_y = i2c_read_ack(); 
    lsb_y = i2c_read_ack(); 
    msb_z = i2c_read_ack(); 
    lsb_z = i2c_read_ack(); 
               
    i2c_resetbus(); 
    
    X_axis = createIntFromChars(msb_x, lsb_x);
    Z_axis = createIntFromChars(msb_y, lsb_y);
    Y_axis = createIntFromChars(msb_z, lsb_z); 
};     

void calculateHeading();    // Takes the buffer data and calculates a heading