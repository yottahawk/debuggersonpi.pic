/* 
 * File: indicators_switches.h
 * Author: Harry    
 * Comments: Contains the methods for reading the switches, and writing to the 
 * LED to indicate any desirable breakpoints in the code. 
 * Revision history: 
 */

/*
 * The momentary push switch is configured as an interrupt-on-change. The pin 
 * will be read whenever the _CNInterrupt is triggered, and is used to break from 
 * the state machine, and start the state machine.
 */

/*
 * The DIP switches will be used to configure the desired state to enter when the 
 * momentary button is pressed. This is used to start the processing in the 
 * desired state. 
 */
void readDIP(unsigned int *tempRegister);


/*
 * The tri-colour led  will be switchable on/off independently using the below
 * methods. These should be used for debugging, and to indicate salient points 
 * in the operation of the machine.
 */
void grnLedOn(void);
void grnLedOff(void);

void blueLedOn(void);
void blueLedOff(void);

void redLedOn(void);
void redLedOff(void);