/* 
 * File:   ENCODE2Peripheral.h
 * Author: Luke
 *
 * Created on 28 January 2026, 23:57
 */

#ifndef ENCODE2PERIPHERAL_H
#define	ENCODE2PERIPHERAL_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    char ReadENCODE2();
    
    //Functions to read and write to the peripheral's buffer
    int WriteENCODE2Buffer(char Data);
    char* ReadENCODE2Buffer(int Count);
    
    int ReadENCODE2Integral();
    int ResetENCODE2Integral();
    
    //Functions to Initiate / Clear
    int InitiateENCODE2();
    int ClearENCODE2Buffer();

#ifdef	__cplusplus
}
#endif

#endif	/* ENCODE2PERIPHERAL_H */

