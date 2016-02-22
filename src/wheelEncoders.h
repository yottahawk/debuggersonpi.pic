/* 
 * File:   wheelEncoders.h
 * Author: Harry
 *
 * Created on 28 January 2016, 23:57
 */

/*
 * The global count registers are named "GLOBAL_enc1_count" and "GLOBAL_enc2_count"
 * The registers are of type int so can store a current count up to 2^16. (65536)
 * 
 * At maximum speed the wheels rotate at approx. 5 rev / sec, which translates
 * to approx 150 high/low transitions per second. Therefore, an int buffer is 
 * easily large enough to store the count for a couple of seconds of operation.
 */

#ifndef debuggersonpi_pic_wheelencoders_h
#define debuggersonpi_pic_wheelencoders_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

// Counter registers accessed by interrupts to increment
extern int GLOBAL_enc1_count;
extern int GLOBAL_enc2_count;

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

// Initialise interrupts (counter increments happen within the ISR) 
void enc1_setupInterrupt();
void enc2_setupInterrupt();

int enc1_readValue();
int enc2_readValue(); 

// Reset value of GLOBAL counter to 0.
void enc1_resetCounter();
void enc2_resetCounter();

// Reset counter, and also return the last value held.
int enc1_Store();
int enc2_Store();
int enc1_resetAndStore();
int enc2_resetAndStore();

// Write new value to global limit register
void enc1_writeCounterLimit(int limit);
void enc2_writeCounterLimit(int limit);
void encAvg_writeCounterLimit(int limit);

/* Write new value to limit register, corresponding to an argument of required 
 * distance to travel. This distance is not necessarily the total distance 
 * covered by the robot, but the total distance rotated by the wheel. */ 
void enc1_writeCounterLimitDistance(int distance_mm);
void enc2_writeCounterLimitDistance(int distance_mm);
void encAvg_writeCounterLimitDistance(int distance_mm);

// Call this function every poll loop to check the limit condition, and set flag if true.
void enc_flagCounterComplete();

////////////////////////////////////////////////////////////////////////////////
#endif //debuggersonpi_pic_wheelencoders_h

