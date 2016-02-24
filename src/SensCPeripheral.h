/* 
 * File:   SENSCPeripheral.h
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#ifndef SENSCPERIPHERAL_H
#define	SENSCPERIPHERAL_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    unsigned int ReadSENSC();
    
    //Functions to read and write to the peripheral's buffer
    void WriteSENSCBuffer(unsigned int Data);
    void ReadSENSCBuffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENSC();
    int ClearSENSCBuffer();

#ifdef	__cplusplus
}
#endif

#endif	/* SENSCPERIPHERAL_H */

