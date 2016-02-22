/* 
 * File: adc.h  
 * Author: Harry    
 * Comments: Methods for initialising and using the adc to sample both the 
 * reflective sensors for line tracking, and the battery voltage.
 * Revision history: 
 */

#ifndef debuggersonpi_pic_adc_h
#define debuggersonpi_pic_adc_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"


/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

// Line Tracking

// setup the adc to take scan and take sequential readings of all 4 sensors.
void adc_linetrackinginit();
// execute scan and write values to tempBuffer[3]
void adc_linetracking_sample(unsigned int tempBuffer[3]);

// Battery Voltage Read

// setup the adc to take a single reading of the V_BATT_SENSE_ADC pin
void adc_vbattinit();
// execute single reading and write to int at dereferenced address of *sample_ptr
void vbatt_sample(int* sample_ptr);

#endif //debuggersonpi_pic_adc_h


