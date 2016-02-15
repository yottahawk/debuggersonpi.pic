/*
 * File:   main.c
 * Author: 
 *
 * Created on 30 January 2016, 16:57
 */

////////////////////////////////////INCLUDES////////////////////////////////////
#include <xc.h>

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

////////////////////////////////////FUNCTIONS///////////////////////////////////

// main loop of execution - anything not interrupt driven goes here
int main(void) 
{
    /* Setup all pins as inputs/outputs and drive outputs to default values */
    initialise_pinmap();            

    IEC1bits.CNIE = 1;              // Enable CN interrupts
    CNEN1bits.CN6IE = 1;            // Enable PUSH_CW interrupt-on-change notification.
    
    led_init_timer();               // enables tmr5 interrupts for led flashing routines.
    led_flash_blue_on(0xFFFF);
    
    // Drive motor wheels for testing purposes.
    enableMotorPSU();               // Set enable line to enable psu.
    
    //R_motor_constSpeed(FWD, 125);
    L_motor_constSpeed(REV, 65);
    
    int i = 0;
    for (i; i<= 1000; i++)
    {
       initCompass(); 
    }
//    
//
//    unsigned char A = readCompass(Config_Reg_A);
//    unsigned char B = readCompass(Config_Reg_B);
//    unsigned char M = readCompass(Mode_Reg);
    
//    readCompassData(); // dummy read
//    
//    unsigned char status1 = readCompass(Status_Reg);
//    // while(!PORTDbits.RD5){};  // DRDY pin is set when data is ready
//    writeCompass(Mode_Reg, Mode_Data); 
//    unsigned char status2 = readCompass(Status_Reg);
//    readCompassData();
//    unsigned char status3 = readCompass(Status_Reg);
    
    
    while(1)
    {  
        // if(spi_info.command) SPI_Function();
        
    }
    
    return 0;
}

