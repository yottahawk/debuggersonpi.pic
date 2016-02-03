/* 
 * File: main.h 
 * Author: Harry
 * Comments: Main header file for PIC software. 
 * Revision history: 
 */

// Header Guard
#ifndef XC_HEADER_GUARD
#define	XC_HEADER_GUARD

///////////////////////////INCLUDES/////////////////////////////////////////////

#include "xc.h" // include processor files - each processor file is guarded.  

#include "config.h" // Configuration registers, IO ports, 

// Peripheral init & access methods
#include "adc.h"
#include "timers.h"
#include "oc.h"
#include "interrupts.h"
#include "indicators_switches.h"
// #include "spi.h"     // HARRY
// #include "i2c.h"     // HARRY    
// #include "grabmtr.h" // HARRY

// Application layer processing - line tracking, PID, intersection detection, 
// tracking encoder count, cube front sense, acceleration profiles, turn left/right,
// grabber motor close/open, 


// Communication Interface PIC-PI
// #include "PIcomms.h"     // LUKE

// State Machine
// #include "topLvlStateM.h"    // LUKE


#endif	/* XC_HEADER_TEMPLATE_H */


