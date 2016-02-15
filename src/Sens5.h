/* 
 * File:   Sens5.h
 * Author: Luke
 *
 * Created on 14 February 2016, 17:41
 */

#ifndef SENS5_H
#define	SENS5_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    char ReadSENS5();
    
    //Functions to read and write to the peripheral's buffer
    int WriteSENS5Buffer(char Data);
    void ReadSENS5Buffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENS5();
    int ClearSENS5Buffer();


#ifdef	__cplusplus
}
#endif

#endif	/* SENS5_H */

