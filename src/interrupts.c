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
    * INT1 - WHEEL_ENC_1
    * This ISR increments the value of the encoder 2 counter when triggered. 
    */
    IFS1bits.INT1IF = 0;        // Reset interrupt flag
    
    GLOBAL_enc1_count++;
}


void __attribute__((__interrupt__, auto_psv)) _INT2Interrupt(void)
{
    /*
     * INT2 - WHEEL_ENC_2
     * This ISR increments the value of the encoder 2 counter when triggered. 
     */
    IFS1bits.INT2IF = 0;        // Reset interrupt flag
    
    GLOBAL_enc2_count++;
}

/*
 * Interrupt-on-change - (PUSH_SW, SENS_L, SENS_R, SENS_FRONT, SENS_CUBE)
 * This ISR should check which value out of the above inputs has changed since 
 * last read. It should compare them against a buffer containing all the 
 * previous values. To keep the ISR short, simply read all the inputs and then 
 * write them to a temporary buffer.
 */
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
           
           I2C2_resetbus();
           
//           Xupper = readCompass(X_MSB_Reg);
//           Xlower = readCompass(X_LSB_Reg);
//           Yupper = readCompass(Y_MSB_Reg);
//           Ylower = readCompass(Y_LSB_Reg);
                 
           break;
   }
           
//   readDIP( &DIPstatus );
    
}
 
/*
 * 
 */
void __attribute__((__interrupt__, auto_psv)) _SPI2Interrupt(void)
{
    
} 

/*
 * ADC Conversion Complete Interrupt
 * This ISR triggers when the ADC conversion is complete, and the ADC buffer is
 * filled with all relevant data. 
 */
void __attribute__((__interrupt__, auto_psv)) _ADC1Interrupt(void)
{
    
} 

/*
 * Timer 1 expired interrupt
 * This ISR is used to poll all sensors that need to be polled. It will execute,
 * and then any data processing that needs to occur should run in the main 
 * execution path, subject to further interrupts.
 */
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void)
{
    
} 

/*
 * Timer 5 expired interrupt
 * This ISR is used as a general purpose timer.
 */
void __attribute__((__interrupt__, auto_psv)) _T5Interrupt(void)
{
    IFS1bits.T5IF = 0;          // Reset TMR5 interrupt flag
    
    if (global_blue_flash == 1){LATEbits.LATE5 = ~LATEbits.LATE5;} // Flash GRN off/on
    if (global_red_flash == 1){LATEbits.LATE6 = ~LATEbits.LATE6;}  // Flash RED off/on
    if (global_grn_flash == 1){LATEbits.LATE7 = ~LATEbits.LATE7;}  // Flash BLUE off/on
    
} 