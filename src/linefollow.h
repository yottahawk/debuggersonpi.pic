/* 
 * File: linefollow.h  
 * Author: Harry Callahan
 * 
 * Comments: Methods to control line following mode.  
 * 
 * Revision history: 
 */

#ifndef debuggersonpi_pic_linefollow_h
#define debuggersonpi_pic_linefollow_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"

#include "adc.h"
#include "compass.h"
#include "pid.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

void linefollow_updatecv(pid_ctrl controller1);
void linefollow_calcpairdiffs(unsigned int * adc_sample_data_ptr , signed int * temp_diffs_ptr);
void linefollow_estimateangle_ldr();
void linefollow_estimateangle_compass();
void linefollow_estimateangle_total();

#endif //debuggersonpi_pic_linefollow_h
