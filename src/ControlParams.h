/* 
 * File:   ControlParams.h
 * Author: Luke
 *
 * Created on 03 February 2016, 23:27
 */

#ifndef CONTROLPARAMS_H
#define	CONTROLPARAMS_H

#ifdef	__cplusplus
extern "C" {
#endif

//Control Parameters relating to wheels
#define MAX_VELOCITY 1          //Maximum velocity in (m/s)
#define ACCEL_TIME 1            //Optimum acceleration time (s)
#define MAX_ACCELERATION (MAX_VELOCITY / ACCEL_TIME) //Calculated acceleration
#define OFFSET_WHEEL_1 0        //Voltage offset for wheel 1?
#define OFFSET_WHEEL_2 0        //Voltage offste for wheel 2?
    
//Control Parameters for timing
#define TIMESTEP 1              //Polling timer interval in us
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* CONTROLPARAMS_H */

