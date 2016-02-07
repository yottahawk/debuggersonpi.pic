/*
 * File:   timers.c
 * Author: Harry
 *
 * Created on 31 January 2016, 23:42
 */
#include <xc.h>

#include "timers.h"

/*
 * Timer 2 is used with output compare modules OC2 and OC3 to drive motor 1 in
 * forward(OC2) or reverse(OC3). The same timer is attached to either module.  
 */
void TMR2init()
{
    T2CONbits.TON = 0;          // Initially set timer off.
    T2CONbits.TSIDL = 0;        // Operation continues in idle mode.
    T2CONbits.TGATE = 0;        // Gated time accumulation disabled.
    T2CONbits.TCKPS = 0b00;     // 1:1 pre-scaler
    T2CONbits.T32 = 0;          // 16 bit timer (not 32)
    T2CONbits.TCS = 0;          // use internal clock.
    
    // need to set the timer period register PR2 before setting TON = 1;
    // also enable interrupts if using.
}

/*
 * Timer 3 is used with output compare modules OC4 and OC5 to drive motor 2 in
 * forward(OC4) or reverse(OC4). The same timer is attached to either module.  
 */
void TMR3init()
{
    T3CONbits.TON = 0;          // Initially set timer off.
    T3CONbits.TSIDL = 0;        // Operation continues in idle mode.
    T3CONbits.TGATE = 0;        // Gated time accumulation disabled.
    T3CONbits.TCKPS = 0b00;     // 1:1 pre-scaler
    T3CONbits.TCS = 0;          // use internal clock.
    
    // need to set the timer period register PR3 before setting TON = 1;
    // also enable interrupts if using.
}