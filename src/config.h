/* 
 * File:   
 * Author: Harry
 * 
 * Comments: Contains functions to perform various config operations that must 
 * execute before the main program can begin.
 * 
 * Revision history: 
 */

#ifndef debuggersonpi_pic_linefollow_h
#define debuggersonpi_pic_linefollow_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

// Sets the TRIS,LAT,ODC and AD1PCGF registers with default values for all pins.
void initialise_pinmap();

#endif //debuggersonpi_pic_linefollow_h



