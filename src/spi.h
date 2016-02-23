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


#include "Sens1Peripheral.h"
#include "Sens2Peripheral.h"
#include "Sens3.h"
#include "Sens4.h"
#include "Sens5.h"
#include "Sens6.h"
#include "SensCubePeripheral.h"
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
    
    //Initialise SPI code - includes interrupt setup
    void Initialise_SPI();
       
    //Discrete SPI function handler
    void SPI_Function();

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

