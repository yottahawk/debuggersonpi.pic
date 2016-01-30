/* 
 * File:   PeripheralTemplate.h
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#ifndef <CAPSFILENAME>_H
#define	<CAPSFILENAME_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    int ReadPeripheral();
    
    
    //Functions to read and write to the peripheral's buffer
    int WritePeripheralBuffer(int Data);
    int* ReadPeripheralBuffer(int Count);
    //Also includes a function to read from "special" value
    //i.e. Integral for wheel encoders
    int ReadPeripheralIntegral();
    
    
    //Functions to Initiate / Clear
    int InitiatePeripheral();
    int ClearBuffer();


#ifdef	__cplusplus
}
#endif

#endif	/* <CAPSFILENAME>_H */

