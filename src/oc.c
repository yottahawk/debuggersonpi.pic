/*
 * File:   oc.c
 * Author: Harry
 *
 * Created on 01 February 2016, 00:07
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "oc.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

void OC2init()
{
    /*
    * This method initialises the OC2 module for PWM mode with FAULT disabled 
    * A 0% initial duty cycle is set to start the module but receive no output.
    * TMR2 is set as the source. 
    */
  
    OC2CONbits.OCSIDL = 0;
    OC2CONbits.OCFLT = 0;
    OC2CONbits.OCTSEL = 0;      // TMR2 is clock source
    OC2CONbits.OCM = 0b110;     // PWM mode, fault pin disabled.
    
    TMR2init();                 // Initialise timer 2
    // PR2 = 0x0080;               // This value sets the PWM period as 31.250 kHz
    PR2 = 0x0320;               // This value sets the PWM period as 20.000 kHz (using PLL -> CLK = 16Mhz)
    
    OC2R = 0x00;                // Init compare register 1 with 0. 
    OC2RS = 0x00;               // Init secondary compare register with 0. 
    
    T2CONbits.TON = 1;          // Set timer2 on.
    
    /* 
    * Now need to setup interrupts if required. 
    * The desired duty cycle is set using the function OC2dutyset().
    * The module is stopped by calling OC2stop().
    */
}

void OC2dutyset(int newdutycycle)
{
    /*
    * This method sets the duty cycle of the PWM generated by the OC2 module. The
    * OC2init() method must have been run to set up the peripheral. The new duty
    * should be passed as an int between 0 and 127. (0x0000 and 0x007F)
    */
    
    OC2RS = newdutycycle;
}

void OC2stop()
{
    /*
     * This method sets a PWM duty cycle of 0, effectively stopping the module,
     * but without disabling it or changing any of the configuration values. 
     * It is equivalent to calling OC2dutyset(0).
     * 
     * This function does not give a defined state(1 or 0) to the output pin.
     * It should be followed by writing to LATDbits.LATD1 bit to set a state.
     */
    
    OC2RS = 0;
}

void OC3init()
{
    /*
    * This method initialises the OC3 module for PWM mode with FAULT disabled 
    * A 0% initial duty cycle is set to start the module but receive no output.
    * TMR2 is set as the source. 
    */
    
    OC3CONbits.OCSIDL = 0;
    OC3CONbits.OCFLT = 0;
    OC3CONbits.OCTSEL = 0;      // TMR2 is clock source
    OC3CONbits.OCM = 0b110;     // PWM mode, fault pin disabled.
    
    TMR2init();                 // Initialise timer 2
    // PR2 = 0x0080;               // This value sets the PWM period as 31.250 kHz
    PR2 = 0x0320;               // This value sets the PWM period as 20.000 kHz (using PLL -> CLK = 16Mhz)
    
    OC3R = 0;                // Init compare register 1 with 0. 
    OC3RS = 0;               // Init secondary compare register with 0. 
    
    T2CONbits.TON = 1;          // Set timer2 on.
    
    /* 
    * Now need to setup interrupts if required. 
    * The desired duty cycle needs to be set by writing to 
    * the secondary compare register OC3RS. The duty cycle is set and reset 
    * using the function OC3dutyset().
    */
}

void OC3dutyset(int newdutycycle)
{
    /*
    * This method sets the duty cycle of the PWM generated by the OC2 module. The
    * OC3init() method must have been run to set up the peripheral. The new duty
    * should be passed as an int between 0 and 127. (0x0000 and 0x007F)
    */ 
    
    OC3RS = newdutycycle;
}

void OC3stop()
{
    /*
     * This method sets a PWM duty cycle of 0, effectively stopping the module,
     * but without disabling it or changing any of the configuration values. 
     * It is equivalent to calling OC3dutyset(0).
     * 
     * This function does not give a defined state(1 or 0) to the output pin.
     * It should be followed by writing to LATDbits.LATD1 bit to set a state.
     */
    
    OC3RS = 0;
}

void OC4init()
{
    /*
    * This method initialises the OC4 module for PWM mode with FAULT disabled 
    * A 0% initial duty cycle is set to start the module but receive no output.
    * TMR3 is set as the source. 
    */
    
    OC4CONbits.OCSIDL = 0;
    OC4CONbits.OCFLT = 0;
    OC4CONbits.OCTSEL = 1;      // TMR3 is clock source
    OC4CONbits.OCM = 0b110;     // PWM mode, fault pin disabled.
    
    TMR3init();                 // Initialise timer 3
    // PR2 = 0x0080;               // This value sets the PWM period as 31.250 kHz
    PR3 = 0x0320;               // This value sets the PWM period as 20.000 kHz (using PLL -> CLK = 16Mhz)
    
    OC4R = 0x00;                // Init compare register 1 with 0. 
    OC4RS = 0x00;               // Init secondary compare register with 0. 
    
    T3CONbits.TON = 1;          // Set timer on.
    
    
    /* 
    * Now need to setup interrupts if required. 
    * The desired duty cycle needs to be set by writing to 
    * the secondary compare register OC4RS. The duty cycle is set and reset 
    * using the function OC4dutyset().
    */
}

void OC4dutyset(int newdutycycle)
{
    /*
    * This method sets the duty cycle of the PWM generated by the OC2 module. The
    * OC2init() method must have been run to set up the peripheral. The new duty
    * should be passed as an int between 0 and 127. (0x0000 and 0x007F)
    */
    
    OC4RS = newdutycycle;
}

void OC4stop()
{
    /*
     * This method sets a PWM duty cycle of 0, effectively stopping the module,
     * but without disabling it or changing any of the configuration values. 
     * It is equivalent to calling OC4dutyset(0).
     * 
     * This function does not give a defined state(1 or 0) to the output pin.
     * It should be followed by writing to LATDbits.LATD1 bit to set a state.
     */
    
    OC4RS = 0;
}

void OC5init()
{
    /*
    * This method initialises the OC4 module for PWM mode with FAULT disabled 
    * A 0% initial duty cycle is set to start the module but receive no output.
    * TMR3 is set as the source. 
    */
    
    OC5CONbits.OCSIDL = 0;
    OC5CONbits.OCFLT = 0;
    OC5CONbits.OCTSEL = 1;      // TMR3 is clock source
    OC5CONbits.OCM = 0b110;     // PWM mode, fault pin disabled.
    
    TMR3init();                 // Initialise timer 2
    // PR2 = 0x0080;               // This value sets the PWM period as 31.250 kHz
    PR3 = 0x0320;               // This value sets the PWM period as 20.000 kHz (using PLL -> CLK = 16Mhz)
    
    OC5R = 0x00;                // Init compare register 1 with 0. 
    OC5RS = 0x00;               // Init secondary compare register with 0. 
    
    T3CONbits.TON = 1;          // Set timer on.
    
    /* 
    * Now need to setup interrupts if required. 
    * The desired duty cycle needs to be set by writing to 
    * the secondary compare register OC5RS. The duty cycle is set and reset 
    * using the function OC5dutyset().
    */
}

void OC5dutyset(int newdutycycle)
{
    /*
    * This method sets the duty cycle of the PWM generated by the OC2 module. The
    * OC5init() method must have been run to set up the peripheral. The new duty
    * should be passed as an int between 0 and 127. (0x0000 and 0x007F)
    */
    
    OC5RS = newdutycycle;
}

void OC5stop()
{
    /*
     * This method sets a PWM duty cycle of 0, effectively stopping the module,
     * but without disabling it or changing any of the configuration values. 
     * It is equivalent to calling OC5dutyset(0).
     * 
     * This function does not give a defined state(1 or 0) to the output pin.
     * It should be followed by writing to LATDbits.LATD1 bit to set a state.
     */
    
    OC5RS = 0;
}