/* 
 * File:   
 * Author: 
 * Comments: Functions are defined to allow the indicator led's to be controlled. 
 * Constant colour, and flashing functions are defined. 
 * 
 * TMR 5 is used to 
 * 
 * Revision history: 
 */

///////////////////////////////GLOBALS//////////////////////////////////////////



//////////////////////////////DECLARATIONS//////////////////////////////////////

void led_init_timer();

void led_TMR5_off_all();

void led_const_blue_on();
void led_const_blue_off();
void led_const_red_on();
void led_const_red_off();
void led_const_grn_on();
void led_const_grn_off();

void led_flash_blue_on(unsigned int period);
void led_flash_red_on(unsigned int period);
void led_flash_grn_on(unsigned int period);

