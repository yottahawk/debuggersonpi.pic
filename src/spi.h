/* 
 * File:   spi.h
 * Author: Luke
 *
 * Created on 04 February 2016, 20:58
 */

#include <xc.h>

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif
    //structure holding data for discrete spi_function
    typedef struct {
        uint8_t      command;            //command byte
        uint16_t     number_of_bytes;    //number of bytes
        uint8_t      buffer[256];        //Input buffer (Note: DIFFERENT to output buffer)
    } spi_info_t;
    spi_info_t spi_info;
    
    //Initialise SPI code - includes interrupt setup
    void Initialise_SPI();
    
    //SPI Interrupt code
    void SPI_Interrupt();
    
    //Discrete SPI function handler
    void SPI_Function();

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

