/* 
 * File:   SENS2Peripheral.h
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#ifndef SENS2PERIPHERAL_H
#define	SENS2PERIPHERAL_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    unsigned int ReadSENS2();
    
    //Functions to read and write to the peripheral's buffer
    void WriteSENS2Buffer(unsigned int Data);
    void ReadSENS2Buffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENS2();
    int ClearSENS2Buffer();

#ifdef	__cplusplus
}
#endif

#endif	/* SENS2PERIPHERAL_H */

