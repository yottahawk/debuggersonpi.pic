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

#ifndef debuggersonpi_pic_led_h
#define debuggersonpi_pic_led_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"

#include "timers.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

// Binary flags used to signal TMR5 to control flashing led routines
extern int global_blue_flash;
extern int global_red_flash;
extern int global_grn_flash;

typedef enum
{
    ALL_OFF         = 0x00,
    BLUE_ON         = 0x01,
    BLUE_OFF        = 0x02,
    RED_ON          = 0x03,
    RED_OFF         = 0x04,
    GREEN_ON        = 0x05,
    GREEN_OFF       = 0x06,
    BLUE_FLASH      = 0x07,
    GREEN_FLASH     = 0x08
            
} led_state;

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

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

#endif //debuggersonpi_pic_led_h




