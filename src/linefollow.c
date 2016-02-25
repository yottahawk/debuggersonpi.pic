/*
 * File:   linefollow.c
 * Author: Harry
 *
 * Created on February 13, 2016, 5:56 PM
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "linefollow.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////////FUNCTIONS///////////////////////////////////

/* -----------------------------------------------------------------------------
 * Function: linefollow_calcpairdiffs(unsigned int adc_samples[4], diffs[2])
 * 
 * Calculates the difference values for the two pairs of line tracking LDR's.
 * Writes the difference values to a struct passed as an input.
 * 
 * INPUTS: Pointer to adc sample data
 *         Pointer to temporary struct for holding difference values
 * 
 * OUTPUTS: None
 * 
 */
void linefollow_calcpairdiffs(unsigned int * adc_sample_data_ptr , signed int * temp_diffs_ptr)
{
    signed int temp_diffs1 = 0;
    signed int temp_diffs2 = 0;
    
    temp_diffs1 = (* adc_sample_data_ptr) - (* (adc_sample_data_ptr + 1));
    temp_diffs1 = (* (adc_sample_data_ptr + 2)) - (* (adc_sample_data_ptr + 3));
    
    * temp_diffs_ptr = temp_diffs1;
    * (temp_diffs_ptr + 1) = temp_diffs2;
}

/* -----------------------------------------------------------------------------
 * Function: linefollow_estimateangle_ldr()
 * 
 * Takes the two difference values calculated from the LDR pairs, and estimates 
 * the robot angular deviation from the straight line.
 * The robot geometry is used here.
 */
signed int linefollow_estimateangle_ldr(signed int * diffs_ptr)
{
    return * diffs_ptr;      // return front sensors pair difference
}

/* -----------------------------------------------------------------------------
 * Function: linefollow_estimateangle_compass()
 * 
 * Estimates the angle between the robot heading and the line using the compass
 * heading.
 * 
 * INPUTS: 
 * 
 * OUTPUTS:
 * 
 */
signed int linefollow_estimateangle_compass()
{
    return 0;
}

/* -----------------------------------------------------------------------------
 * Function: linefollow_estimateangle_total();
 * 
 * Uses the angle estimates from the LDR's and the compass to create a single 
 * estimate.
 * 
 * INPUTS:
 * 
 * OUTPUTS:
 * 
 */
signed int linefollow_estimateangle_total()
{
    return 0;
}