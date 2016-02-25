#ifndef debuggersonpi_pic_breakcondtions_h
#define debuggersonpi_pic_breakcondtions_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"

#include "datatypes.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

void bc_counts_LorR(control_variables * local_state_vars_ptr);
void bc_counts_LandR(control_variables * local_state_vars_ptr);


void bc_counts_L(control_variables * local_state_vars_ptr);
void bc_counts_R(control_variables * local_state_vars_ptr);

void angle_smallerror(control_variables * local_state_vars_ptr);

void detectIntersection(control_variables * local_state_vars_ptr);

#endif //debuggersonpi_pic_breakcondtions_h