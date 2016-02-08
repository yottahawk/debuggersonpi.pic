/* 
 * File: oc.h
 * Author: Harry
 * 
 * Comments: The output compare modules are used to generate PWM outputs that 
 * drive the ZXBM5210 driver IC's that control the drive wheels. The duty cycle
 * of the PWM signals determines the rotational velocity of the wheels, and 
 * therefore the duty cycle will be directly controllable.
 * 
 * This file contains methods to access the Output Compare module at the lowest 
 * level, starting and stopping any of the modules with a PWM frequency of 31.250kHz.
 * There are also methods to set the duty cycle of the PWM signal. 
 * 
 * The wheels.h and wheels.c files use these lowest level methods to control the 
 * movement of the robot at a higher level.
 * 
 * Revision history: 
 */

/*
 * To start the Output Compare modules, first call the init() methods. 
 * This init's the OC module as well as the associated timer used to run it. 
 * The modules utilise the following timers...
 * TMR2 = OC2 and OC3 (Motor 1)
 * TMR3 = OC4 and OC5 (Motor 2)
 * The dutyset() methods can now be used to change the PWM duty cycle, passing an 
 * int between 0 and 127 for a duty cycle between 0% and 100%.
 */

// R - FWD
void OC2init();
void OC2dutyset(int newdutycycle);
void OC2stop();

// R - REV
void OC3init();
void OC3dutyset(int newdutycycle);
void OC3stop();

// L - REV
void OC4init();
void OC4dutyset(int newdutycycle);
void OC4stop();

// L - FWD
void OC5init();
void OC5dutyset(int newdutycycle);
void OC5stop();