/* 
 * File:   SENSLPeripheral.h
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#ifndef SENSLPERIPHERAL_H
#define	SENSLPERIPHERAL_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define BUFFER_LENGTH 256
    
    //Function to read a value directly from the peripheral
    unsigned int ReadSENSL();
    
    extern unsigned int SENSLBuffer[BUFFER_LENGTH];
    //Functions to read and write to the peripheral's buffer
    void WriteSENSLBuffer(unsigned int Data);
    void ReadSENSLBuffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENSL();
    int ClearSENSLBuffer();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSLPERIPHERAL_H */

