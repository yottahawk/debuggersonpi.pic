/*
 * File:   interrupts.c
 * Author: Harry
 *
 * Created on 02 February 2016, 00:34
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "interrupts.h"
#include "compass.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

int CNbuffer[4];
int DIPstatus;

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

void __attribute__((__interrupt__, auto_psv)) _INT1Interrupt(void)
{
    /*
    ** INT1 - WHEEL_ENC_1
    ** This ISR increments the value of the encoder 2 counter when triggered. 
    */
    
    IFS1bits.INT1IF = 0;        // Reset interrupt flag
    
    GLOBAL_enc1_count++;
}


void __attribute__((__interrupt__, auto_psv)) _INT2Interrupt(void)
{
    /*
    ** INT2 - WHEEL_ENC_2
    ** This ISR increments the value of the encoder 2 counter when triggered. 
    */
    
    IFS1bits.INT2IF = 0;        // Reset interrupt flag
    
    GLOBAL_enc2_count++;
    
    if (LATEbits.LATE5)
    {
        led_const_blue_on();
    }
    else
    {
         led_const_blue_off();
    }
   
}

void __attribute__((__interrupt__, auto_psv)) _CNInterrupt(void)
{
    /*
     * This ISR is triggered by any of the enabled interrupt-on-change inputs when
     * that particular pin is enabled. 
     * 
     * There are 4 interrupt-on-change inputs that may trigger the interrupt.
     * PUSH_SW
     * SENS_FRONT
     * SENS_L
     * SENS_R
     * 
     * The PUSH_SW input is triggered by the user pressing the momentary button.
     * It is used to trigger the start/stop of programs/test states.
     * 
     * The three SENS inputs are connected to 
     */
   IFS1bits.CNIF = 0;       // Reset interrupt flag 
    
   CNbuffer[1] = PORTBbits.RB4;     // PUSH_SW
   CNbuffer[2] = PORTBbits.RB12;    // SENS_CUBE
   CNbuffer[3] = PORTBbits.RB13;    // SENSE_L
   CNbuffer[4] = PORTBbits.RB3;     // SNESE_R
  
   unsigned char A;
   
   unsigned char Xupper;
   unsigned char Xlower;
   unsigned char Yupper;
   unsigned char Ylower;
   
   switch(CNbuffer[1])
   {
       case 0:
            break;
       case 1:
#ifdef I2C1_enable    
            I2C1_resetbus();
#endif
#ifdef I2C2_enable
            I2C2_resetbus();
#endif
            enc1_resetCounter();
            enc2_resetCounter();
           
           break;
   }
           
//   readDIP( &DIPstatus );
    
}
 
//SPI Interrupt code
void __attribute__((__interrupt__, auto_psv)) _SPI2Interrupt(void) {   
    //When interrupt triggers, data has been received in Buffer.
    unsigned int command = (unsigned int) SPI2BUF;
    
    if(command) {
        //First data in buffer is always command word!   
        spi_info.command = command; 
        //Remaining data goes in "info" buffer
        for(int i=0;i<7;i++) spi_info.info[i] = (unsigned int) SPI2BUF;
    }

    //Ensure the receive buffer is empty;
    for(int i=0;i<8;i++) {unsigned int empty = SPI2BUF;}
    
    //clear interrupt flag?
    IFS2bits.SPI2IF = 0;        //Clear bit 1
    SPI2STATbits.SPIROV = 0;    //Clear SPIROV bit
    
    //Reset SPI module (tends to get out of sync)
    SPI2STATbits.SPIEN = 0;
    SPI2STATbits.SPIEN = 1;
}

void __attribute__((__interrupt__, auto_psv)) _ADC1Interrupt(void)
{
    /*
    ** ADC Conversion Complete Interrupt
    ** This ISR triggers when the ADC conversion is complete, and the ADC buffer is
    ** filled with all relevant data. 
    */
    
} 

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void)
{
    /*
    ** Timer 1 expired interrupt
    ** This ISR is used to poll all sensors that need to be polled. It will execute,
    ** and then any data processing that needs to occur should run in the main 
    ** execution path, subject to further interrupts.
    */
    
} 

void __attribute__((__interrupt__, auto_psv)) _T5Interrupt(void)
{
    /*
    ** Timer 5 expired interrupt
    ** This ISR is used as a general purpose timer.
    */
    IFS1bits.T5IF = 0;          // Reset TMR5 interrupt flag
    
    if (global_blue_flash == 1){LATEbits.LATE5 = ~LATEbits.LATE5;} // Flash GRN off/on
    if (global_red_flash == 1){LATEbits.LATE6 = ~LATEbits.LATE6;}  // Flash RED off/on
    if (global_grn_flash == 1){LATEbits.LATE7 = ~LATEbits.LATE7;}  // Flash BLUE off/on
    
} 