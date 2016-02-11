/*
 * File:   main.c
 * Author: 
 *
 * Created on 30 January 2016, 16:57
 */

////////////////////////////////////INCLUDES////////////////////////////////////
#include "xc.h"

#include "config.h"
#include "oc.h"
#include "motors.h"
#include "led.h"
#include "interrupts.h"
#include "indicators_switches.h"
#include "Encoder1Peripheral.h"

////////////////////////////////////FUNCTIONS///////////////////////////////////

// main loop of execution - anything not interrupt driven goes here
int main(void) 
{
    initialise_pinmap();
    
    IEC1bits.CNIE = 1;      // Enable CN interrupts
    CNEN1bits.CN6IE = 1;    // Enable PUSH_CW interrupt-on-change notification.
            
    LATBbits.LATB14 = 1;    // enable motor power supply.
    led_init_timer();             // enables tmr5 interrupts for led flashing routines.
    
    R_motor_constSpeed(FWD, 25);
    L_motor_constSpeed(REV, 25);
   
    // Enable INT1 interrupts, triggering on negative edge of WHEEL_ENC_1 signal.
    IEC1bits.INT1IE = 1;    // Enable interrupt 
    
    // Enable INT2 interrupts, triggering on negative edge of WHEEL_ENC_2 signal.
    IEC1bits.INT2IE = 1;    // Enable interrupt 
    
    while(1)
    {  
    }
    
    return 0;
}

