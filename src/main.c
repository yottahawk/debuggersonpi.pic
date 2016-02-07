/*
 * File:   main.c
 * Author: 
 *
 * Created on 30 January 2016, 16:57
 */
#include "xc.h"

#include "config.h"
#include "oc.h"

// main loop of execution - anything not interrupt driven goes here
int main(void) 
{
    initialise_pinmap();
    
    IEC1bits.CNIE = 1;   // Enable CN interrupts
    CNEN1bits.CN6IE = 1; // Enable PUSH_CW interrupt-on-change notification.
            
    
    // LATBbits.LATB14 = 1; // enable motor power supply.
    
    // OC2init();
    // OC2dutyset(125);
    
    // OC5init();
    // OC5dutyset(125);
    
    while(1)
    {
        
    }
    
    return 0;
}

