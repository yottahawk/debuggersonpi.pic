/* 
 * File: oc.h
 * Author: Harry
 * Comments: The output compare modules are used to generate PWM outputs that 
 * drive the ZXBM5210 driver IC's that control the drive wheels. The duty cycle
 * of the PWM signals determines the rotational velocity of the wheels, and 
 * therefore the duty cycle will be directly controllable. 
 * 
 * Revision history: 
 */

/*
 * To start the outputcompare modules, first call the init() method. This init's
 * the OC module as well as the associated timer used to run it. The modules 
 * TMR2 = OC2 and OC3 (Motor 1)
 * TMR3 = OC4 and OC5 (Motor 2)
 * The dutyset() methods are now used to change the PWM duty cycle, by passing an 
 * int between 0 and 127 for a duty cycle between 0% and 100%.
 */

void OC2init();
void OC2dutyset(int newdutycycle);

void OC3init();
void OC3dutyset(int newdutycycle);

void OC4init();
void OC4dutyset(int newdutycycle);

void OC5init();
void OC5dutyset(int newdutycycle);