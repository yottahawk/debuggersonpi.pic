/* 
 * File:   StateMachine.h
 * Author: Luke
 *
 * Created on 02 February 2016, 19:54
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

#ifdef	__cplusplus
extern "C" {
#endif

//Enumerated Type for various states
typedef enum {
    //***********************************************************************//
    //Motor Driving States
    STOPPED         = 0x80, //Stationary
    
    //Open Loop States        
    OL_FORWARD      = 0x81, //Open Loop Forward drive
    OL_LEFT         = 0x82, //Open Loop Forwards Left turn (90)
    OL_RIGHT        = 0x83, //Open Loop Forwards Right turn (90)
    OL_REVERSE      = 0x84, //Open Loop Reverse
    OL_REV_LEFT     = 0x85, //Open Loop Reverse Left Turn (90)
    OL_REV_RIGHT    = 0x86, //Open Loop Reverse Right Turn (90)
            
    //Closed Loop with Compass states
    COMP_FORWARD    = 0x87, //Closed Loop With Compass Forward drive
    COMP_LEFT       = 0x88, //Closed Loop With Compass Forwards Left turn (90)
    COMP_RIGHT      = 0x89, //Closed Loop With Compass Forwards Right turn (90)
    COMP_REVERSE    = 0x8A, //Closed Loop With Compass Reverse
    COMP_REV_LEFT   = 0x8B, //Closed Loop With Compass Reverse Left Turn (90)
    COMP_REV_RIGHT  = 0x8C, //Closed Loop With Compass Reverse Right Turn (90)      
            
    //Closed Loop with Encoders states
    ECDR_FORWARD    = 0x8D, //Closed Loop With Encoders Forward drive
    ECDR_LEFT       = 0x8E, //Closed Loop With Encoders Forwards Left turn (90)
    ECDR_RIGHT      = 0x8F, //Closed Loop With Encoders Forwards Right turn (90)
    ECDR_REVERSE    = 0x90, //Closed Loop With Encoders Reverse
    ECDR_REV_LEFT   = 0x91, //Closed Loop With Encoders Reverse Left Turn (90)
    ECDR_REV_RIGHT  = 0x92, //Closed Loop With Encoders Reverse Right Turn (90) 
            
    //Closed Loop with Analog Sensors states
    PSNS_FORWARD    = 0x93, //Closed Loop With PhotoSensors Forward drive
    PSNS_LEFT       = 0x94, //Closed Loop With PhotoSensors Forwards Left turn (90)
    PSNS_RIGHT      = 0x95, //Closed Loop With PhotoSensors Forwards Right turn (90)
    PSNS_REVERSE    = 0x96, //Closed Loop With PhotoSensors Reverse
    PSNS_REV_LEFT   = 0x97, //Closed Loop With PhotoSensors Reverse Left Turn (90)
    PSNS_REV_RIGHT  = 0x98, //Closed Loop With PhotoSensors Reverse Right Turn (90)     
} state_t;

//enumerated type for various commands
typedef enum {
    //Grabber commands
    OPEN_GRABBER = 0x01,
    CLOSE_GRABBER = 0x02,
    READ_GRABBER = 0x03,
            
    //Motor Commands
    WRITE_MOTOR1 = 0x04,
    READ_MOTOR1 = 0x05,
    WRITE_MOTOR2 = 0x06,
    READ_MOTOR2 = 0x07,
            
    //Encoder Commands
    READ_ECDR1 = 0x08,
    READ_ECDR1_INT = 0x09,
    READ_ECDR2 = 0x0A,
    READ_ECDR2_INT = 0x0B,
            
    //Compass commands
    READ_COMP = 0x0C,

    //Photosensor commands
    READ_PSNS1 = 0x0D,
    READ_PSNS2 = 0x0E,
    READ_PSNS3 = 0x0F,
    READ_PSNS4 = 0x10,
    READ_PSNS5 = 0x11,
    READ_PSNS6 = 0x12
} command_t;

state_t Curr_State, Next_State; 

#ifdef	__cplusplus
}
#endif

#endif	/* STATEMACHINE_H */

