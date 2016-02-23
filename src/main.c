/*
 * File:   main.c
 * Author: 
 *
 * Created on 30 January 2016, 16:57
 */

////////////////////////////////////INCLUDES////////////////////////////////////
#include "xc.h"

#include "StateMachine.h"
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

//functions for testing here - above main so no need for forward declaration
void testFunctionEncoders()
{
    enc1_setupInterrupt();
    enc2_setupInterrupt();
    
    IEC1bits.CNIE = 1;              // Enable CN interrupts
    CNEN1bits.CN6IE = 1;            // Enable PUSH_CW interrupt-on-change notification.
    
}


// main loop of execution - anything not interrupt driven goes here
int main(void) 
{
    /* Setup all pins as inputs/outputs and drive outputs to default values */
    initialise_pinmap(); 
    
    // setup interrupt priorities
    
    // Create default state tracking struct 
    spi_state_data spi_newstate = {
        .state = STOPPED,
        .state_data.data_type = NONE,
        .state_data.value = 0
    };
    spi_state_data * spi_newstate_ptr = &spi_newstate;
    
    while(1){
    // interrupt or poll SPI here to collect next state information
    
        if (spi_newstate.state != STOPPED)
        {
            state_handler(spi_newstate_ptr);
        }
    // return here when state completes.
    
    }      
    
    return 0;
}


