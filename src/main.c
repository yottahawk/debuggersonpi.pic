/*
 * File:   main.c
 * Author: 
 *
 * Created on 30 January 2016, 16:57
 */

////////////////////////////////////INCLUDES////////////////////////////////////
#include "xc.h"

#include "config.h"
#include "oc.h"
#include "motors.h"
#include "led.h"
#include "interrupts.h"
#include "indicators_switches.h"
#include "wheelEncoders.h"
#include "spi.h"

////////////////////////////////////FUNCTIONS///////////////////////////////////

// main loop of execution - anything not interrupt driven goes here
int main(void) 
{
    /* Setup all pins as inputs/outputs and drive outputs to default values */
    initialise_pinmap();            
    

    IEC1bits.CNIE = 1;              // Enable CN interrupts
    CNEN1bits.CN6IE = 1;            // Enable PUSH_CW interrupt-on-change notification.
    
    
    led_init_timer();               // enables tmr5 interrupts for led flashing routines.
    
    // Drive motor wheels for testing purposes.
    enableMotorPSU();               // Set enable line to enable psu.
    
    R_motor_constSpeed(FWD, 25);
    L_motor_constSpeed(REV, 25);
    
    spi_info_t* info;
    info = get_spi_info();
    
    while(1)
    {  
        if(info->command) SPI_Function();
    }
    
    return 0;
}

