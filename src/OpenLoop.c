#include "OpenLoop.h"
#include "ControlParams.h"
#include "Motor1Peripheral.h"

void ol_forward() {
    //Read current speed (from motor)
    int v_m1 = ReadMOTOR1Peripheral();
    int v_m2 = ReadMOTOR2Peripheral();
    
    //estimate that current speed is the average of the two
    //Note use of "<<" bitshift operator for quick /2
    int v_curr = (v_m1+v_m2) << 1;
    int v_next = 0;
    
    //if the current speed is less than the maximum, increase it by
    //the allowable acceleration. Otherwise, just set it to maximum.
    if (v_curr < MAX_VELOCITY) v_next = v_curr + MAX_ACCELERATION * TIMESTEP;
    else v_next = MAX_VELOCITY;
    
    //Write v_next to both motors
    WriteMOTOR1Peripheral(v_next);
    WriteMOTOR2Peripheral(v_next);
}

void ol_reverse() {
    //Read current speed (from motor)
    int v_m1 = ReadMOTOR1Peripheral();
    int v_m2 = ReadMOTOR2Peripheral();
    
    //estimate that current speed is the average of the two
    //Note use of "<<" bitshift operator for quick /2
    int v_curr = (v_m1+v_m2) << 1;
    int v_next = 0;
    
    //if the current speed is greater than the negative maximum, decrease it by
    //the allowable acceleration. Otherwise, just set it to the negative maximum.
    if (v_curr > -1*MAX_VELOCITY) v_next = v_curr - MAX_ACCELERATION * TIMESTEP;
    else v_next = -1*MAX_VELOCITY;
    
    //Write v_next to both motors
    WriteMOTOR1Peripheral(v_next);
    WriteMOTOR2Peripheral(v_next);
}

