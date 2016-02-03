/*
 * File:   indicators_switches.c
 * Author: Harry
 *
 * Created on 02 February 2016, 21:32
 */

#include "indicators_switches.h"

void readDIP(unsigned int *tempRegister)
{
    unsigned int sw1 = PORTE & 0b0000000000000010; // DIP_SW1
    unsigned int sw2 = PORTE & 0b0000000000000100; // DIP_SW2
    unsigned int sw3 = PORTE & 0b0000000000001000; // DIP_SW3
    unsigned int sw4 = PORTE & 0b0000000000010000; // DIP_SW4
    
    *tempRegister = (sw1 & sw2 & sw3 & sw4);
}

// Turn on green led
void grnLedOn(void)
{
    LATEbits.LATE6 = 0; 
}

// Turn off green led
void grnLedOn(void)
{
    LATEbits.LATE6 = 1; 
}

// Turn on blue led
void blueLedOn(void)
{
    LATEbits.LATE5 = 0; 
}

// Turn off blue led
void blueLedOn(void)
{
    LATEbits.LATE5 = 1; 
}

// Turn on red led
void redLedOn(void)
{
    LATEbits.LATE7 = 0; 
}

// Turn off red led
void redLedOn(void)
{
    LATEbits.LATE7 = 1; 
}
