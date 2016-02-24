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

// #define testmode
#define operatingmode

////////////////////////////////////FUNCTIONS///////////////////////////////////

//functions for testing here - above main so no need for forward declaration
void testFunctionEncoders()
{
    IEC1bits.CNIE = 1;              // Enable CN interrupts
    CNEN1bits.CN6IE = 1;            // Enable PUSH_CW interrupt-on-change notification.
    
    enc1_setupInterrupt();
    enc2_setupInterrupt();
    
    enableMotorPSU();
    
    L_motor_constSpeed(FWD, 200);
    
    while(1){};
}

void testLoadState(spi_state_data * spi_newstate_ptr)
{
    spi_newstate_ptr->state = PSNS_FORWARD;
    spi_newstate_ptr->state_data.data_type = SPEED;
    spi_newstate_ptr->state_data.value = 150;
}

////////////////////////////////////////////////////////////////////////////////

// main loop of execution - anything not interrupt driven goes here
int main(void) 
{
    /* Setup all pins as inputs/outputs and drive outputs to default values */
    initialise_pinmap(); 
    
#ifdef testmode
    // TESTFUNCTIONS GO HERE
    led_const_blue_on();
    testFunctionEncoders();
#endif //testmode
    
#ifdef operatingmode
    // setup interrupt priorities
    
    // Create default state tracking struct 
    spi_state_data spi_newstate = {
        .state = STOPPED,
        .state_data.data_type = NONE_CONDITION_T,
        .state_data.value = 0
    };
    spi_state_data * spi_newstate_ptr = &spi_newstate;
    
    testLoadState(spi_newstate_ptr);
    
    while(1){
    // interrupt or poll SPI here to collect next state information
    
        if (spi_newstate.state != STOPPED)
        {
            state_handler(spi_newstate_ptr);
        }
    // return here when state completes.
    
    }      
    
#endif //operating mode
    return 0;
}


