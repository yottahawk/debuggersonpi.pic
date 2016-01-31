/* 
 * File:   SENSCUBEPeripheral.h
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#ifndef SENSCUBEPERIPHERAL_H
#define	SENSCUBEPERIPHERAL_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    char ReadSENSCUBE();
    
    //Functions to read and write to the peripheral's buffer
    int WriteSENSCUBEBuffer(char Data);
    char* ReadSENSCUBEBuffer(int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENSCUBE();
    int ClearSENSCUBEBuffer();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSCUBEPERIPHERAL_H */

