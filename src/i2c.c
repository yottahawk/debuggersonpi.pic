/*
 * File:   i2c.c
 * Author: Harry
 *
 * Created on February 8, 2016, 10:29 PM
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "i2c.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

void i2c_resetbus()
{
    I2C1CONbits.PEN = 1;                        // initiate stop condition as master
    
    // wait for hardware clear of stop bit
    while (I2C1CONbits.PEN){}
    
    I2C1CONbits.RCEN        = 0;                // Disable receive as master
    IFS1bits.MI2C1IF        = 0;                // Clear interrupt
    I2C1STATbits.IWCOL      = 0;                // Reset write collision flag
    I2C1STATbits.BCL        = 0;                // Reset bus collision flag
}

void i2c_init(int Baud_Rate)
{
    int clearbuffertemp;
    
    // Set baud rate using I2C1BRG
    // With Fosc = 4Mhz...
    // I2C1BRG = 39 -> 100kHz clock
    // I2C1BRG = 79 -> 50 kHz clock
    
    I2C1CONbits.I2CEN       = 0;                // Disable I2C mode
    
    I2C1BRG = Baud_Rate;                        // Set new baud rate
    I2C1CONbits.DISSLW      = 1;                // Disable slew rate control
    IFS1bits.MI2C1IF        = 0;                // Clear interrupt
    I2C1CONbits.I2CEN       = 1;                // Enable I2C mode
    
    clearbuffertemp         = I2C1RCV;          // read receive buffer to clear buffer
    i2c_resetbus();                             // set bus to idle
}

void i2c_start()
{
    I2C1CONbits.ACKDT       = 0;                // Reset any previous ack
    I2C1CONbits.SEN         = 1;                // Initiate start condition
    
    // Wait for the hardware to automatically clear the start bit
    while (I2C1CONbits.SEN){}                   
}

void i2c_repeatstart()
{
   I2C1CONbits.RSEN = 1;                        //Initiate repeatedstart condition
    
   // Wait for hardware to automatically clear the reset bit
   while (I2C1CONbits.RSEN){}
}

unsigned char send_i2c_byte(unsigned char data)
{
   while (I2C1STATbits.TBF){}                   // Wait for transmission to complete
  
   IFS1bits.MI2C1IF = 0;                        // Clear Interrupt
   I2C1TRN = data;                              // load the outgoing data byte

   // wait for transmission to complete
   while (I2C1STATbits.TRSTAT){};

   // Check for ACK from slave, abort if not found
   if (I2C1STATbits.ACKSTAT == 1) // Slave sends NACK
   {
      led_const_grn_on();
      return(1);
   }
   
   return(0);               // transmission completed successfully
}

unsigned char i2c_read_ack()
{
   unsigned char temp = 0; 
   
   // Check lower 5 bits of I2C1CON register are all 0
   if (!(I2C1CON & 0x001F)){};
   
   //set I2C module to receive
   I2C1CONbits.RCEN = 1;
   
   while (I2C1CONbits.RCEN){};
   while (!I2C1STATbits.RBF){};
   temp = I2C1RCV; //get data from I2C1RCV register
   
   I2C1CONbits.ACKEN = 1;       // Ack
   
   //return data
   return temp;
}

unsigned char i2c_read_no_ack()
{
   unsigned char temp = 0; 
    
   //set I2C module to receive
   I2C1CONbits.RCEN = 1;
   
   while (!I2C1STATbits.RBF){};
        
   temp = I2C1RCV; //get data from I2C1RCV register
   
   //return data
   return temp;
}