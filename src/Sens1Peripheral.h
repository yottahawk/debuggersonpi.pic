/* 
 * File:   SENS1Peripheral.h
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#ifndef SENS1PERIPHERAL_H
#define	SENS1PERIPHERAL_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    char ReadSENS1();
    
    //Functions to read and write to the peripheral's buffer
    int WriteSENS1Buffer(char Data);
    void ReadSENS1Buffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENS1();
    int ClearSENS1Buffer();

#ifdef	__cplusplus
}
#endif

#endif	/* SENS1PERIPHERAL_H */

