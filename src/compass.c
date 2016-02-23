/* 
 * File:   compass.c
 * Author: Harry
 *
 * Created on February 13, 2016, 11:21 PM
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "compass.h"

#include "math.h"
#include "hs_math.h"

/////////////////////////////////////DEFINES////////////////////////////////////

#define PI 3.14

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

// Externals
int currentheading;             // Value of current heading
int prevheadings[100];          // Buffer containing previous headings

// Internals
signed int X_axis;              // Stores the X_axis gauss value
signed int Y_axis;              // Stores the Y_axis gauss value
signed int Z_axis;              // Stores the Z_axis gauss value

int m_scale = 1;

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

/* -----------------------------------------------------------------------------
 * Function: periph_readCompass(unsigned char reg_address)
 * 
 * Reads the value of a register on the HMC5883L compass.
 * 
 * INPUTS: register address
 *  
 * OUTPUTS: unsigned char contents of register
 */
unsigned char periph_readCompass(unsigned char reg_address)
{
    // Read the value of a certain register
    UINT8 val; 
    
    periph_StartI2C1();
    periph_WriteByteI2C1(HMC5883L_ADDR | SLAVE_WRITE_TO);
    periph_WriteByteI2C1(reg_address);

    periph_StartI2C1();
    periph_WriteByteI2C1(HMC5883L_ADDR | SLAVE_READ_FROM);
    periph_ReadByteI2C1(&val);
    
    periph_StopI2C1();
    
    return val;
} 

/* -----------------------------------------------------------------------------
 * Function: periph_writeCompass(unsigned char reg_address , unsigned char value)
 * 
 * Writes a given value to a register on the HMC5883L compass.
 * 
 * INPUTS: register address, unsigned char data to be written to register
 *  
 * OUTPUTS: none
 */
void periph_writeCompass(unsigned char reg_address, unsigned char value)
{
    // Writes to a register  
    periph_StartI2C1();
    
    periph_WriteByteI2C1(HMC5883L_ADDR | SLAVE_WRITE_TO);
    periph_WriteByteI2C1(reg_address);
    periph_WriteByteI2C1(value);
    
    periph_StopI2C1();
}

/* -----------------------------------------------------------------------------
 * Function: initCompass()
 * 
 * Initialises the HMC5883L compass over an i2c communications channel. 
 * Sets up the Config and Mode registers.
 * 
 * INPUTS: none
 * 
 * OUTPUTS: none
 */
void initCompass()
{
    periph_OpenI2C1();
    
    periph_writeCompass(Config_Reg_A, Config_A_Data); 
    periph_writeCompass(Config_Reg_B, Config_B_Data); 
    periph_writeCompass(Mode_Reg, Mode_Data_Continuous);  
}

void selfTestCompass(); // Run self test and verify pass

void setGain(set_gauss_scale gauss)     // Use an enum to set the gauss scale
{
    unsigned char value = 0;    
    
    if(gauss == 0.88)        
    {                                            
      value = 0x00;                      
      m_scale = 0.73; 
   }  
    
   else if(gauss == 1.3)    
   { 
      value = 0x20; 
      m_scale = 0.92;      
   }  
    
   else if(gauss == 1.9) 
   { 
      value = 0x40; 
      m_scale = 1.22; 
   } 
    
   else if(gauss == 2.5) 
   { 
      value = 0x60; 
      m_scale = 1.52; 
   }  
    
   else if(gauss == 4.0) 
   { 
      value = 0x80; 
      m_scale = 2.27; 
   } 
    
   else if(gauss == 4.7) 
   { 
      value = 0xA0; 
      m_scale = 2.56; 
   }  
    
   else if(gauss == 5.6) 
   { 
      value = 0xC0; 
      m_scale = 3.03; 
   }    
    
   else if(gauss == 8.1)                                  
   { 
      value = 0xE0; 
      m_scale = 4.35;          
   }        
                                                
   value <<= 5; 
   periph_writeCompass(Config_Reg_B, value); 
}

/* -----------------------------------------------------------------------------
 * Function: createIntFromChars(unsigned char MSB, unsigned char LSB)
 * 
 * Creates an int data type from two chars, where one char is the MSByte and the
 * other is the LSByte. 
 * 
 * INPUTS: MSbyte, LSbyts
 * 
 * OUTPUTS: returns Int.
 * 
 */
int createIntFromChars(unsigned char LSB, unsigned char MSB)
{
    signed int val = 0; 
                               
    val = LSB; 
    val <<= 8;                          
    val |= MSB;          
    return val;    
}; 

/* -----------------------------------------------------------------------------
 * Function: readCompassData()
 * 
 * Reads all 6 compass data registers, and creates ints for the field strength 
 * on each axis. 
 * 
 * INPUTS: None
 *
 * OUTPUTS: Writes field strength ints to globals X,Y and Z_axis.
 */
void readCompassData()
{
    // Reads the relevant data to a buffer
    UINT8 data[6] = {0};
    
    UINT8 * data_ptr;
    data_ptr = &data[0];
    
    periph_StartI2C1(); 
    periph_WriteByteI2C1(HMC5883L_ADDR | SLAVE_WRITE_TO);        // Write    
    periph_WriteByteI2C1(X_MSB_Reg);  
    periph_StartI2C1(); 
    periph_WriteByteI2C1(HMC5883L_ADDR | SLAVE_READ_FROM);       // Read
    periph_ReadBytesAckI2C1( data_ptr , 6 );          
    periph_StopI2C1();
    
    X_axis = createIntFromChars(data[0], data[1]);  // LSB , MSB
    Z_axis = createIntFromChars(data[2], data[3]);  // LSB , MSB
    Y_axis = createIntFromChars(data[4], data[5]);  // LSB , MSB
};  

/* -----------------------------------------------------------------------------
 * Function: calculateHeading();
 * 
 * Uses the field strength ints to calculate a heading. 
 * 
 * INPUTS: Field strength int globals X,Y and Z_axis.
 * 
 * OUTPUT: int heading written to global current_heading.
 */
int calculateHeading()
{ 
    /*Now use atan_int
    
    float X_scaled = X_axis * m_scale;
    float Y_scaled = Y_axis * m_scale;
    float Z_scaled = Z_axis * m_scale;
    
    float temp_heading;
    
    temp_heading = atan2(Y_scaled , X_scaled);
    
    if(temp_heading < 0.0) 
    { 
      currentheading += (2.0 * PI); 
    } 
    
    if(temp_heading > (2.0 * PI))                
    {                            
      currentheading -= (2.0 * PI); 
    }                    
                    
    temp_heading *= (180.0 / PI);*/
    
    int degrees = atan_int(X_axis, Y_axis);
    
    //???
    currentheading = degrees;
    
    // now convert to meaningful integer that pid controller can interpret
    
    return currentheading;
    
   // currentheading = currentheading + (int)declination_angle;
}

////////////////////////////////////////////////////////////////////////////////
