/* 
 * File:   SENSRPeripheral.h
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#ifndef SENSRPERIPHERAL_H
#define	SENSRPERIPHERAL_H

#ifdef	__cplusplus
extern "C" {
#endif
    #define BUFFER_LENGTH 256
    
    //Function to read a value directly from the peripheral
    unsigned int ReadSENSR();
    
    extern unsigned int SENSRBuffer[BUFFER_LENGTH];
    //Functions to read and write to the peripheral's buffer
    void WriteSENSRBuffer(unsigned int Data);
    void ReadSENSRBuffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENSR();
    int ClearSENSRBuffer();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSRPERIPHERAL_H */

