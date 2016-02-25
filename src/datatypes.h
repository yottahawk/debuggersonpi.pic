/* 
 * File:   datatypes.h
 * Author: Harry
 *
 * Created on 03 February 2016, 23:27
 */

#ifndef debuggersonpi_pic_datatypes_h
#define debuggersonpi_pic_datatypes_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"

#include "pid.h"        // pid_ctrl struct defined here
#include "motors.h"     // motor direction type struct defined here

/////////////////////////////////////DEFINES////////////////////////////////////

////////////////////////////////TYPEDEFS,ENUMS,STRUCTS//////////////////////////

// Operating States
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
    PSNS_FORWARD_JUNCTION_DETECT = 0x99,        // Closed Loop, Photosensors, Junction Detect

    //Grabber commands
    OPEN_GRABBER = 0x01,
    CLOSE_GRABBER = 0x02,
    READ_GRABBER = 0x03,
            
    //Encoder Commands
    READ_ECDR1      = 0x08,
    READ_ECDR1_SUM  = 0x09,
    READ_ECDR2      = 0x0A,
    READ_ECDR2_SUM  = 0x0B,
            
    //Compass commands
    READ_COMP = 0x0C,

    //Photosensor commands
    READ_PSNS1 = 0x0D,
    READ_PSNS2 = 0x0E,
    READ_PSNS3 = 0x0F,
    READ_PSNS4 = 0x10,
    READ_PSNS5 = 0x11,
    READ_PSNS6 = 0x12,
    READ_PSNSFNT = 0x13,
    READ_PSNSCBE = 0x14,
            
    READ_ROOM = 0x30,
            
    //Operate LED
    WRITE_LED = 0x15,
            
    //Read DIP Switches
    READ_DIP = 0x16,
            
    //Motor Commands
    WRITE_MOTOR_LEFT_FWD = 0x20,
    WRITE_MOTOR_LEFT_REV = 0x21, 
            
    WRITE_MOTOR_RIGHT_FWD = 0x23,
    WRITE_MOTOR_RIGHT_REV = 0x24,       
               
} state_t;

typedef enum 
{
    NONE_CONDITION_T, 
    COUNTS,
    JUNCTION 
} condition_t;

typedef struct {
    condition_t data_type;
    unsigned int value;
} state_conditions_t; 

/* -----------------------------------------------------------------------------
 * ENUM to clearly illustrate when a break condition is set.
 */
typedef enum {
    STATE_CONTINUE,
    STATE_BREAK
} boolean_breakstate;

/* -----------------------------------------------------------------------------
 * Enum to hold the intersection types, and used to indicate which intersection 
 * has been detected.
 */
typedef enum 
{
	ERoom_Empty,
	ERoom_Cross,
	ERoom_NorthSouth,
	ERoom_EastWest,
	ERoom_EastSouthWest,
	ERoom_NorthSouthWest,
	ERoom_NorthEastWest,
	ERoom_NorthEastSouth,
	ERoom_NorthWest,
	ERoom_NorthEast,
	ERoom_EastSouth,
	ERoom_SouthWest,
	ERoom_North,
	ERoom_East,
	ERoom_South,
	ERoom_West,
	ERoom_Unknown
} ERoom;


typedef enum{
    USESENSORS_FALSE,
    USESENSORS_TRUE
} use_sensors;

/* -----------------------------------------------------------------------------
 * Value to hold any data used in the current state, passed from the SPI command.
 */
typedef struct
{
    state_t state;                       // current state (0 is default)
    state_conditions_t state_data;       // current state 

} spi_state_data;

/* -----------------------------------------------------------------------------
 * Struct to hold data to be written out over spi
 */
typedef struct
{
    unsigned int datatype_unsignedint;             // data type to hold spi data out
    signed int datatype_signedint;
} spi_data_out;

/* ----------------------------------------------------------------------------
 * Struct for storage of all variables that need to be tracked throughout 
 * state lifetime.
 */
typedef struct 
{
    //----------------------------------DATA------------------------------------
    unsigned int update_counter;        // increment counter on every update
    boolean_breakstate general_break_condition; 
    
    pid_ctrl Controller1;
    pid_ctrl * pid_ctrl_ptr;
     
    unsigned int psns_prev_digital_samples[4000][3];
    unsigned int psns_adc_samples[4];
    
    unsigned int wheelencL_count;
    unsigned int wheelencR_count;
    
    unsigned int wheelencL_limit;
    unsigned int wheelencR_limit;
    
    unsigned int motor_L_desiredspeed;
    unsigned int motor_R_desiredspeed;
    unsigned int motor_dualspeed;
    
    motor_direction_type motor_L_direction;
    motor_direction_type motor_R_direction;
    motor_direction_type motor_dualdirection;
    
    use_sensors usecompass;
    int compass_currentheading;   // update on measurement
    int compass_desiredheading;   // determined at start of state
    
    use_sensors usepsns;
    int psns_currentheading;
    int psns_desiredheading;
    
    
} control_variables;

/* -----------------------------------------------------------------------------
 * Struct to locally store any break conditions for the current state.
 */ 
typedef struct
{
    
    
} break_conditions_store;



//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

#endif //debuggersonpi_pic_datatypes_h