/*
 * File:   timers.c
 * Author: Harry
 *
 * Created on 31 January 2016, 23:42
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "timers.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

void POllTMRinit()
{
   /*
    * Timer 1 is the poll timer, used to create a regular interval between 
    * sensors being read. 
    * The TMR1 ISR is used to trigger sampling to begin. 
    */ 
    
    T1CONbits.TON = 0;          // Initially set timer off.
    T1CONbits.TSIDL = 0;        // Operation continues in idle mode.
    T1CONbits.TGATE = 0;        // Gated time accumulation disabled.
    T1CONbits.TCS = 0;          // use internal clock.
    
    T1CONbits.TCKPS = 0b00;     // 1:1 pre-scaler
    PR1 = 0xFFFF;   // Sets a timer frequency of 125Hz. (Poll_period = 8ms)
    
    // Enable/Disable poll timer using StartPollTMR() or StopPollTMR();)
}

void StartPollTMR()
{
    T1CONbits.TON = 1;
}

void StopPollTMR()
{
    T1CONbits.TON = 0;
}

void TMR2init()
{
    /*
    * Timer 2 is used with output compare modules OC2 and OC3 to drive motor 1 in
    * forward(OC2) or reverse(OC3). The same timer is attached to either module.  
    */
    
    T2CONbits.TON = 0;          // Initially set timer off.
    T2CONbits.TSIDL = 0;        // Operation continues in idle mode.
    T2CONbits.TGATE = 0;        // Gated time accumulation disabled.
    T2CONbits.TCKPS = 0b00;     // 1:1 pre-scaler
    T2CONbits.T32 = 0;          // 16 bit timer (not 32)
    T2CONbits.TCS = 0;          // use internal clock.
    
    // need to set the timer period register PR2 before setting TON = 1;
    // also enable interrupts if using.
}

void TMR3init()
{
    /*
    * Timer 3 is used with output compare modules OC4 and OC5 to drive motor 2 in
    * forward(OC4) or reverse(OC4). The same timer is attached to either module.  
    */
    
    T3CONbits.TON = 0;          // Initially set timer off.
    T3CONbits.TSIDL = 0;        // Operation continues in idle mode.
    T3CONbits.TGATE = 0;        // Gated time accumulation disabled.
    T3CONbits.TCKPS = 0b00;     // 1:1 pre-scaler
    T3CONbits.TCS = 0;          // use internal clock.
    
    // need to set the timer period register PR3 before setting TON = 1;
    // also enable interrupts if using.
}

void TMR4init(unsigned int period)
{
   /*
    * TMR4 is used as a general purpose timer that different modules can use. 
    * Eg.AccelerationCurveProfile, 
    */ 
    
    T4CONbits.TON = 0;          // Initially set timer off.
    T4CONbits.TSIDL = 0;        // Operation continues in idle mode.
    T4CONbits.TGATE = 0;        // Gated time accumulation disabled.
    T4CONbits.TCS = 0;          // use internal clock.
    
    // Following lines set timer period.
    // T_TMR4 = 8*10^6 / ( pre-scaler * period_register )
    T4CONbits.TCKPS = 0b00;     // 1:1 pre-scaler
    PR4 = period;               // Period register
    
    // Enable/Disable poll timer using StartTMR4() or StopTMR4();)
}

void StartTMR4()
{
    T4CONbits.TON = 1;
}

void StopTMR4()
{
    T4CONbits.TON = 0;
}

void TMR5init(unsigned int period)
{
   /*
    * TMR5 is used as a general purpose timer that different modules can use. 
    * Eg.AccelerationCurveProfile, LED flashing, 
    */ 
    
    T5CONbits.TON = 0;          // Initially set timer off.
    T5CONbits.TSIDL = 0;        // Operation continues in idle mode.
    T5CONbits.TGATE = 0;        // Gated time accumulation disabled.
    T5CONbits.TCS = 0;          // use internal clock.
    
    // Following lines set timer period.
    // T_TMR4 = 8*10^6 / ( pre-scaler * period_register )
    T5CONbits.TCKPS = 0b00;     // 1:1 pre-scaler
    PR5 = period;               // Period register
    
    // Enable/Disable poll timer using StartTMR5() or StopTMR5();)
}

void StartTMR5()
{
    T5CONbits.TON = 1;
}

void StopTMR5()
{
    T5CONbits.TON = 0;
}