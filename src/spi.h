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
        unsigned int    command;    //command word
        unsigned int    info[3];    //3 info bytes
    } spi_info_t;
    spi_info_t spi_info;
    
    const unsigned int DONE = 0x00FE;
    
    //Initialise SPI code - includes interrupt setup
    void Initialise_SPI();
    
    //SPI Interrupt code
    void __attribute__((__interrupt__, auto_psv)) _SPI2Interrupt(void);
    
    //Discrete SPI function handler
    void SPI_Function();

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

