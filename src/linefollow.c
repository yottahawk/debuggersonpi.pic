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
** function: linefollow_updatecv();
** 
** Top-level function for linefollow module.
** Reads adc values, calculates differences, estimates angular deviation from 
** difference pairs.
** 
** INPUTS : local_control_vars_ptr 
** 
** OUTPUTS : updated pid_struct, 
** 
 */
void linefollow_updatecv(pid_ctrl controller1)
{
    // ADC ---------------------------------------------------------------------
    unsigned int adc_samples[4] = 0;
    unsigned int * adc_samples_ptr = &adc_samples;
   
    adc_linetrackinginit();                          // init adc module 
    adc_linetracking_sample(adc_samples_ptr);        // read 4 tracking sensors
    
    signed int diffs[2] = 0;
    signed int * diffs_ptr = &diffs;
    
    linefollow_calcpairdiffs(adc_samples_ptr , diffs_ptr);
    linefollow_estimateangle_ldr(diffs_ptr);
    // Compass -----------------------------------------------------------------
    initCompass();
    readCompassData();
    calculateHeading();
    
    linefollow_estimateangle_compass();
    // PID ---------------------------------------------------------------------
    
    linefollow_estimateangle_total();       // incorporate both ldr and compass
    
    int cv_new;
    cv_new = pid_update();                  // run PID update
    controller1.cv = cv_new;                // update PID struct with new cv
}

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
linefollow_calcpairdiffs(unsigned int * adc_sample_data_ptr , signed int * temp_diffs_ptr)
{
    signed int temp_diffs1;
    signed int temp_diffs2;
    
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
signed int linefollow_estimateangle_ldr()
{
    
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
linefollow_estimateangle_compass()
{
    
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
linefollow_estimateangle_total()
{
    
}