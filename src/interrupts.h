/* 
 * File: interrupts.h 
 * Author: Harry    
 * Comments: Contains all the interrupt setup code, and the interrupt service  
 * routines (ISR's). ISR's will be kept as tight as possible by minimising 
 * function calls. 
 * Revision history: 
 */

/*
 * Required interrupts for operation.
 * 
 * External Interrupts
 * INT1 (WHEEL_ENC_1)
 * INT2 (WHEEL_ENC_2)
 * 
 * Input Change Notification (CN)
 * PUSH_SW
 * SENS_FRONT 
 * SENS_L
 * SENS_R
 * SENS_CUBE (also may use ADC)
 * 
 * Serial Peripheral Interface - PI comms
 * SPI2 Event
 * 
 * ADC
 * ADC1 Conversion Done
 * 
 * Timers
 * Timer1 (Polling sensors)
 * 
 */

#ifndef debuggersonpi_pic_interrupts_h
#define debuggersonpi_pic_interrupts_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"
#include "datatypes.h"

#include "motors.h"
#include "led.h"
#include "indicators_switches.h"
#include "wheelEncoders.h"
#include "spi.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

#endif // debuggersonpi_pic_interrupts_h