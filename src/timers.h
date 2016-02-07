/* 
 * File: timers.h
 * Author: Harry
 * Comments: Provides methods for initialising timers used within various other
 * peripherals and also for polling. 
 * TMR1 = Poll Timer
 * TMR2 = OC2 and OC3 (Motor 1)
 * TMR3 = OC4 and OC5 (Motor 2)
 * TMR4
 * TMR5
 * 
 * Revision history: 
 */

// Initialises TMR1 as the poll timers with an 8ms period.
void POllTMRinit();
void StartPollTMR();
void StopPollTMR();

// Initialises TMR2 for OC2 or OC3, but does not start or set period PR2.
// PR2 is set and timer is started in OC2 and OC3 init methods. (see oc.c)
void TMR2init();

// Initialises TMR3 for OC4 or OC5, but does not start or set period PR3
// PR3 is set and timer is started in OC4 and OC5 init methods. (see oc.c)
void TMR3init();

// General purpose timer. 
void TMR4init(unsigned int setPeriod);
void StartTMR4();
void StopTMR5();
