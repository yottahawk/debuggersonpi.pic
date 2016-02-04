/* 
 * File: timers.h
 * Author: Harry
 * Comments: Provides methods for initialising timers used within various other
 * peripherals and also for polling. 
 * TMR1
 * TMR2 = OC2 and OC3 (Motor 1)
 * TMR3 = OC4 and OC5 (Motor 2)
 * TMR4
 * TMR5
 * 
 * Revision history: 
 */

// Initialises TMR2 for OC2 or OC3, but does not start or set period PR2
void TMR2init();

// Initialises TMR3 for OC4 or OC5, but does not start or set period PR3
void TMR3init();

