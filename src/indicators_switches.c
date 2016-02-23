/*
 * File:   indicators_switches.c
 * Author: Harry
 *
 * Created on 02 February 2016, 21:32
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "indicators_switches.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

void readDIP(unsigned int *tempRegister)
{
    /*
     * Reads the 4 DIP switches, and returns a pointer to an int where the lowest 4 bits
     * represent the state of the switches. The upper 4 bits are all 0.
     */
    
    unsigned int sw1 = PORTE & 0b0000000000000010; // DIP_SW1
    unsigned int sw2 = PORTE & 0b0000000000000100; // DIP_SW2
    unsigned int sw3 = PORTE & 0b0000000000001000; // DIP_SW3
    unsigned int sw4 = PORTE & 0b0000000000010000; // DIP_SW4
    
    *tempRegister = (sw1 | sw2 | sw3 | sw4) >> 1;
}