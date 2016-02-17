/* 
 * File:   OpenLoop.h
 * Author: Luke
 *
 * Created on 03 February 2016, 23:24
 */

#ifndef debuggersonpi_pic_openloop_h
#define debuggersonpi_pic_openloop_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"

#include "ControlParams.h"
// #include "Motor1Peripheral.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

void ol_forward();
void ol_reverse();
void ol_fwd_left();
void ol_fwd_right();
void ol_rev_left();
void ol_rev_right();
void ol_stopped();

#endif //debuggersonpi_pic_openloop_h

