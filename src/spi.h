/* 
 * File:   spi.h
 * Author: Luke
 *
 * Created on 04 February 2016, 20:58
 */

#ifndef SPI_H
#define	SPI_H

#include "xc.h"

#include "StateMachine.h"
#include "datatypes.h"

#include "SensLPeripheral.h"
#include "SensRPeripheral.h"
#include "SensCPeripheral.h"
#include "SensFRONT.h"

#include "compass.h"
#include "wheelEncoders.h"
#include "motors.h"
#include "indicators_switches.h"
#include "led.h"
#include "grabber.h"

#ifdef	__cplusplus
extern "C" {
#endif
    //structure holding data for discrete spi_function
    typedef struct {
        unsigned int    command;    //command word
        unsigned int    info[7];    //3 info bytes
    } spi_info_t;
    extern spi_info_t spi_info;
    
    extern const unsigned int DONE;
    extern const unsigned int Data;
    
    //Write data to SPI
    void Write_SPI(const unsigned int* buffer, unsigned int length);
    
    //Initialise SPI code - includes interrupt setup
    void Initialise_SPI();
       
    //Discrete SPI function handler
    void SPI_Function(spi_state_data* state_data);

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

