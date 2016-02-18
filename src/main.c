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
#include "compass.h"

/////////////////////////////////////DEFINES//////////////////////////////////// 

int heading1;
int heading2;
int heading3;

////////////////////////////////////FUNCTIONS///////////////////////////////////

void testFunctionEncoders()
{
    enc1_setupInterrupt();
    enc2_setupInterrupt();
}


// main loop of execution - anything not interrupt driven goes here
int main(void) 
{
    /* Setup all pins as inputs/outputs and drive outputs to default values */
    initialise_pinmap();            

    IEC1bits.CNIE = 1;              // Enable CN interrupts
    CNEN1bits.CN6IE = 1;            // Enable PUSH_CW interrupt-on-change notification.
    
    led_init_timer();               // enables tmr5 interrupts for led flashing routines.
    // led_flash_blue_on(0xFFFF);
    
    // Drive motor wheels for testing purposes.
    enableMotorPSU();               // Set enable line to enable psu.
    
    testFunctionEncoders();
    
    while(1)
    {  
        if(spi_info.command) SPI_Function();
    }
    
   /* periph_StopI2C1();
    periph_CloseI2C1();
    
    initCompass();
    unsigned char A = periph_readCompass(Config_Reg_A);
    unsigned char B = periph_readCompass(Config_Reg_B);
    unsigned char M = periph_readCompass(Mode_Reg);
    
    
    calculateHeading();
    heading1 = currentheading;
    
    calculateHeading();
    heading2 = currentheading;

    calculateHeading();
    heading3 = currentheading;
    
    A = periph_readCompass(Config_Reg_A);
    B = periph_readCompass(Config_Reg_B);
    M = periph_readCompass(Mode_Reg);
    
    R_motor_constSpeed(FWD, 15);
    L_motor_constSpeed(FWD, 15);
    
    Nop();*/
    
    return 0;
}


