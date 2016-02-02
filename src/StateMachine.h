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
    STOPPED,    //Stationary
    
    //Open Loop States        
    OL_FORWARD,    //Open Loop Forward drive
    OL_LEFT,       //Open Loop Forwards Left turn (90)
    OL_RIGHT,      //Open Loop Forwards Right turn (90)
    OL_REVERSE,    //Open Loop Reverse
    OL_REV_LEFT,   //Open Loop Reverse Left Turn (90)
    OL_REV_RIGHT,  //Open Loop Reverse Right Turn (90)
            
    //Closed Loop with Compass states
    COMP_FORWARD,    //Closed Loop With Compass Forward drive
    COMP_LEFT,       //Closed Loop With Compass Forwards Left turn (90)
    COMP_RIGHT,      //Closed Loop With Compass Forwards Right turn (90)
    COMP_REVERSE,    //Closed Loop With Compass Reverse
    COMP_REV_LEFT,   //Closed Loop With Compass Reverse Left Turn (90)
    COMP_REV_RIGHT,  //Closed Loop With Compass Reverse Right Turn (90)      
            
    //Closed Loop with Encoders states
    ECDR_FORWARD,    //Closed Loop With Encoders Forward drive
    ECDR_LEFT,       //Closed Loop With Encoders Forwards Left turn (90)
    ECDR_RIGHT,      //Closed Loop With Encoders Forwards Right turn (90)
    ECDR_REVERSE,    //Closed Loop With Encoders Reverse
    ECDR_REV_LEFT,   //Closed Loop With Encoders Reverse Left Turn (90)
    ECDR_REV_RIGHT,  //Closed Loop With Encoders Reverse Right Turn (90) 
            
    //Closed Loop with Analog Sensors states
    PSNS_FORWARD,    //Closed Loop With PhototSensors Forward drive
    PSNS_LEFT,       //Closed Loop With PhototSensors Forwards Left turn (90)
    PSNS_RIGHT,      //Closed Loop With PhototSensors Forwards Right turn (90)
    PSNS_REVERSE,    //Closed Loop With PhototSensors Reverse
    PSNS_REV_LEFT,   //Closed Loop With PhototSensors Reverse Left Turn (90)
    PSNS_REV_RIGHT,  //Closed Loop With PhototSensors Reverse Right Turn (90) 
            

            
};


#ifdef	__cplusplus
}
#endif

#endif	/* STATEMACHINE_H */

