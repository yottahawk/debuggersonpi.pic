/* 
 * File:   compass.c
 * Author: Harry
 *
 * Created on February 13, 2016, 11:21 PM
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "compass.h"

#include "math.h"

/////////////////////////////////////DEFINES////////////////////////////////////

// Only define one or the other!
// #define I2C1_enable
#define I2C2_enable

#define PI 3.14

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

// Externals
int currentheading;             // Value of current heading
int prevheadings[100];          // Buffer containing previous headings

// Internals
signed int X_axis;
signed int Y_axis;
signed int Z_axis;

int m_scale = 1;

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

#ifdef I2C1_enable

/* 
 * Initializes the compass over an i2c comms channel. 
 * The comms channel is opened within the init method.
 * The HMC5883L is set up as desired for the given application.
 */
void initCompass()
{
    periph_OpenI2C1();
    
    periph_writeCompass(Config_Reg_A, Config_A_Data); 
    periph_writeCompass(Config_Reg_B, Config_B_Data); 
    periph_writeCompass(Mode_Reg, Mode_Data_Continuous);  
}

void selfTestCompass(); // Run self test and verify pass

void scaleAxis(); // Scale the output of each axis.
void setGain(set_gauss_scale value);     // Use an enum to set the gauss scale

int createIntFromChars(unsigned char MSB, unsigned char LSB)
{
    // Create int from two chars
    
    signed int val = 0; 
                               
    val = MSB; 
    val <<= 8;                          
    val |= LSB;          
    return val;    
}; 

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
    
    X_axis = createIntFromChars(data[0], data[1]);
    Z_axis = createIntFromChars(data[2], data[3]);
    Y_axis = createIntFromChars(data[4], data[5]); 
};     

void calculateHeading()
{
    // Takes the buffer data and calculates a heading
    readCompassData();
    
    int X_scaled = X_axis * m_scale;
    int Y_scaled = Y_axis * m_scale;
    int Z_scaled = Z_axis * m_scale;
    
    currentheading = atan2(Y_scaled , X_scaled);
    
    if(currentheading < 0.0) 
    { 
      currentheading += (2.0 * PI); 
    } 
    
    if(currentheading > (2.0 * PI))                
    {                            
      currentheading -= (2.0 * PI); 
    }                    
                    
   currentheading *= (180.0 / PI);
    
   // currentheading = currentheading + (int)declination_angle;
}

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

void periph_writeCompass(unsigned char reg_address, unsigned char value)
{
    // Writes to a register  
    periph_StartI2C1();
    
    periph_WriteByteI2C1(HMC5883L_ADDR | SLAVE_WRITE_TO);
    periph_WriteByteI2C1(reg_address);
    periph_WriteByteI2C1(value);
    
    periph_StopI2C1();
}

#endif // I2C1_enable

////////////////////////////////////////////////////////////////////////////////

#ifdef I2C2_enable

/* 
 * Initializes the compass over an i2c comms channel. 
 * The comms channel is opened within the init method.
 * The HMC5883L is set up as desired for the given application.
 */
void initCompass()
{
    periph_OpenI2C2();
    
    periph_writeCompass(Config_Reg_A, Config_A_Data); 
    periph_writeCompass(Config_Reg_B, Config_B_Data); 
    periph_writeCompass(Mode_Reg, Mode_Data_Continuous);  
}

void selfTestCompass(); // Run self test and verify pass

void scaleAxis(); // Scale the output of each axis.
void setGain(set_gauss_scale value);     // Use an enum to set the gauss scale

int createIntFromChars(unsigned char MSB, unsigned char LSB)
{
    // Create int from two chars
    
    signed int val = 0; 
                               
    val = MSB; 
    val <<= 8;                          
    val |= LSB;          
    return val;    
}; 

void readCompassData()
{
    // Reads the relevant data to a buffer
    UINT8 data[6] = {0};
    
    UINT8 * data_ptr;
    data_ptr = &data[0];
    
    periph_StartI2C2(); 
    periph_WriteByteI2C2(HMC5883L_ADDR | SLAVE_WRITE_TO);        // Write    
    periph_WriteByteI2C2(X_MSB_Reg);  
    periph_StartI2C2(); 
    periph_WriteByteI2C2(HMC5883L_ADDR | SLAVE_READ_FROM);       // Read
    periph_ReadBytesAckI2C2( data_ptr , 6 );          
    periph_StopI2C2();
    
    X_axis = createIntFromChars(data[0], data[1]);
    Z_axis = createIntFromChars(data[2], data[3]);
    Y_axis = createIntFromChars(data[4], data[5]); 
};     

void calculateHeading()
{
    // Takes the buffer data and calculates a heading
    readCompassData();
    
    int X_scaled = X_axis * m_scale;
    int Y_scaled = Y_axis * m_scale;
    int Z_scaled = Z_axis * m_scale;
    
    currentheading = atan2(Y_scaled , X_scaled);
    
    if(currentheading < 0.0) 
    { 
      currentheading += (2.0 * PI); 
    } 
    
    if(currentheading > (2.0 * PI))                
    {                            
      currentheading -= (2.0 * PI); 
    }                    
                    
   currentheading *= (180.0 / PI);
    
   // currentheading = currentheading + (int)declination_angle;
}

unsigned char periph_readCompass(unsigned char reg_address)
{
    // Read the value of a certain register
    UINT8 val; 
    
    periph_StartI2C2();
    periph_WriteByteI2C2(HMC5883L_ADDR | SLAVE_WRITE_TO);
    periph_WriteByteI2C2(reg_address);

    periph_StartI2C2();
    periph_WriteByteI2C2(HMC5883L_ADDR | SLAVE_READ_FROM);
    periph_ReadByteI2C2(&val);
    
    periph_StopI2C2();
    
    return val;
} 

void periph_writeCompass(unsigned char reg_address, unsigned char value)
{
    // Writes to a register  
    periph_StartI2C2();
    
    periph_WriteByteI2C2(HMC5883L_ADDR | SLAVE_WRITE_TO);
    periph_WriteByteI2C2(reg_address);
    periph_WriteByteI2C2(value);
    
    periph_StopI2C2();
}

#endif // I2C2_enable