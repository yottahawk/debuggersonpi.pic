/*
 * File:   led.c
 * Author: Harry
 * 
 * E5 = BLUE
 * E6 = RED (currently not working)
 * E7 = GREEN
 *
 * Created on February 10, 2016, 8:31 PM
 */

//////////////////////////////////INCLUDES//////////////////////////////////////

#include "xc.h"
#include "led.h"

#include "timers.h"

/////////////////////////////////GLOBALS////////////////////////////////////////
int global_blue_flash = 0;
int global_red_flash = 0;
int global_grn_flash = 0;

/////////////////////////////////FUNCTIONS//////////////////////////////////////

void led_init_timer()
{
    IEC1bits.T5IE = 1;   // Enable timer 5 interrupts
}

void led_TMR5_off_all()
{
    T5CONbits.TON = 0;          // Stop timer 5.
    IEC1bits.T5IE = 0;          // Disable TMR5 interrupt.   
    
    global_blue_flash = 0;
    global_red_flash = 0;
    global_grn_flash = 0;
    
    LATEbits.LATE5 = 1;         // BLUE_LED - off
    LATEbits.LATE6 = 1;         // RED_LED - off
    LATEbits.LATE7 = 1;         // GRN_LED - off
}

void led_const_blue_on()
{
    LATEbits.LATE5 = 0;
}

void led_const_blue_off()
{
    LATEbits.LATE5 = 1;
}

void led_const_red_on()
{
    LATEbits.LATE6 = 0;
}

void led_const_red_off()
{
    LATEbits.LATE6 = 1;
}

void led_const_grn_on()
{
    LATEbits.LATE7 = 0;
}

void led_const_grn_off()
{
    LATEbits.LATE7 = 1;
}

void led_flash_blue_on(unsigned int period)
{
    global_blue_flash = 1;
    
    TMR5init(period);
    T5CONbits.TCKPS = 0b10;
    StartTMR5();
}

void led_flash_red_on(unsigned int period)
{
    global_red_flash = 1;
    
    TMR5init(period);
    T5CONbits.TCKPS = 0b10;
    StartTMR5();
}

void led_flash_grn_on(unsigned int period)
{
    global_grn_flash = 1;
    
    TMR5init(period);
    T5CONbits.TCKPS = 0b10;
    StartTMR5();
}