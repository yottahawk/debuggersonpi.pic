/*
 * File:   oc.c
 * Author: Harry
 *
 * Created on 01 February 2016, 00:07
 */

#include "oc.h"

/*
 * This method initialises the OC2 module for PWM mode with FAULT disabled, a 0% 
 * duty cycle to start the module but receive no output, and with TMR2 as the 
 * source. 
 */
void OC2init()
{
    OC2CONbits.OCSIDL = 0;
    OC2CONbits.OCFLT = 0;
    OC2CONbits.OCTSEL = 0;      // TMR2 is clock source
    OC2CONbits.OCM = 0b110;     // PWM mode, fault pin disabled.
    
    TMR2init();                 // Initialise timer 2
    PR2 = 0x0080;               // Sets PWM period as 31.250 kHz
    
    OC2R = 0x00;                // Init compare register 1 with 0. 
    OC2RS = 0x00;               // Init secondary compare register with 0. 
    
    // now need to setup interrupts if required, and start timer 2 by writing
    // T2CONbits.TON = 1; The desired duty cycle needs to be set by writing to 
    // the secondary compare register OC2RS. The duty cycle is set and reset 
    // using the function OC2dutyset().
}

/*
 * This method sets the duty cycle of the PWM generated by the OC2 module. The
 * OC2init() method must have been run to set up the peripheral. The new duty
 * should be passed as an int between 0 and 127. (0x0000 and 0x007F)
 */
void OC2dutyset(int newdutycycle)
{
    OC2RS = newdutycycle;
}

/*
 * This method initialises the OC2 module for PWM mode with FAULT disabled, a 0% 
 * duty cycle to start the module but receive no output, and with TMR2 as the 
 * source. 
 */
void OC3init()
{
    OC3CONbits.OCSIDL = 0;
    OC3CONbits.OCFLT = 0;
    OC3CONbits.OCTSEL = 0;      // TMR2 is clock source
    OC3CONbits.OCM = 0b110;     // PWM mode, fault pin disabled.
    
    TMR2init();                 // Initialise timer 2
    PR2 = 0x0080;               // Sets PWM period as 31.250 kHz
    
    OC3R = 0x00;                // Init compare register 1 with 0. 
    OC3RS = 0x00;               // Init secondary compare register with 0. 
    
    // now need to setup interrupts if required, and start timer 2 by writing
    // T2CONbits.TON = 1; The desired duty cycle needs to be set by writing to 
    // the secondary compare register OC3RS. The duty cycle is set and reset 
    // using the function OC3dutyset().
}

/*
 * This method sets the duty cycle of the PWM generated by the OC2 module. The
 * OC2init() method must have been run to set up the peripheral. The new duty
 * should be passed as an int between 0 and 127. (0x0000 and 0x007F)
 */
void OC3dutyset(int newdutycycle)
{
    OC3RS = newdutycycle;
}

/*
 * This method initialises the OC2 module for PWM mode with FAULT disabled, a 0% 
 * duty cycle to start the module but receive no output, and with TMR2 as the 
 * source. 
 */
void OC4init()
{
    OC4CONbits.OCSIDL = 0;
    OC4CONbits.OCFLT = 0;
    OC4CONbits.OCTSEL = 0;      // TMR2 is clock source
    OC4CONbits.OCM = 0b110;     // PWM mode, fault pin disabled.
    
    TMR3init();                 // Initialise timer 2
    PR3 = 0x0080;               // Sets PWM period as 31.250 kHz
    
    OC4R = 0x00;                // Init compare register 1 with 0. 
    OC4RS = 0x00;               // Init secondary compare register with 0. 
    
    // now need to setup interrupts if required, and start timer 2 by writing
    // T3CONbits.TON = 1; The desired duty cycle needs to be set by writing to 
    // the secondary compare register OC2RS. The duty cycle is set and reset 
    // using the function OC2dutyset().
}

/*
 * This method sets the duty cycle of the PWM generated by the OC2 module. The
 * OC2init() method must have been run to set up the peripheral. The new duty
 * should be passed as an int between 0 and 127. (0x0000 and 0x007F)
 */
void OC4dutyset(int newdutycycle)
{
    OC4RS = newdutycycle;
}

/*
 * This method initialises the OC2 module for PWM mode with FAULT disabled, a 0% 
 * duty cycle to start the module but receive no output, and with TMR2 as the 
 * source. 
 */
void OC5init()
{
    OC5CONbits.OCSIDL = 0;
    OC5CONbits.OCFLT = 0;
    OC5CONbits.OCTSEL = 0;      // TMR2 is clock source
    OC5CONbits.OCM = 0b110;     // PWM mode, fault pin disabled.
    
    TMR3init();                 // Initialise timer 2
    PR3 = 0x0080;               // Sets PWM period as 31.250 kHz
    
    OC5R = 0x00;                // Init compare register 1 with 0. 
    OC5RS = 0x00;               // Init secondary compare register with 0. 
    
    // now need to setup interrupts if required, and start timer 2 by writing
    // T2CONbits.TON = 1; The desired duty cycle needs to be set by writing to 
    // the secondary compare register OC2RS. The duty cycle is set and reset 
    // using the function OC2dutyset().
}

/*
 * This method sets the duty cycle of the PWM generated by the OC2 module. The
 * OC2init() method must have been run to set up the peripheral. The new duty
 * should be passed as an int between 0 and 127. (0x0000 and 0x007F)
 */
void OC5dutyset(int newdutycycle)
{
    OC5RS = newdutycycle;
}