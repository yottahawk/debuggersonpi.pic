/*
 * File:   interrupts.c
 * Author: Harry
 *
 * Created on 02 February 2016, 00:34
 */
#include <xc.h>
#include "interrupts.h"
#include "motors.h"

//////////////////////////GLOBAL VARIABLES//////////////////////////////////////
int CNbuffer[4];


//////////////////////////FUNCTIONS/////////////////////////////////////////////
/*
 * INT1 - WHEEL_ENC_1
 * This ISR should increment the value of a counter every time it is triggered. 
 */
void __attribute__((__interrupt__, auto_psv)) _INT1Interrupt(void)
{
    
}

/*
 * INT2 - WHEEL_ENC_2
 * This ISR should increment the value of a counter every time it is triggered. 
 */
void __attribute__((__interrupt__, auto_psv)) _INT2Interrupt(void)
{
    
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
   CNbuffer[1] = PORTBbits.RB4;     // PUSH_SW
   CNbuffer[2] = PORTBbits.RB12;    // SENS_CUBE
   CNbuffer[3] = PORTBbits.RB13;    // SENSE_L
   CNbuffer[4] = PORTBbits.RB3;     // SNESE_R
  
   switch(CNbuffer[1])
   {
       case 0:
           break;
       case 1:
           // LATBbits.LATB14 = ~LATBbits.LATB14;
           IncrementWiper();
           break;
   }
           
   IFS1bits.CNIF = 0;
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