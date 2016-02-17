/* 
 * File:   Sens4.h
 * Author: Luke
 *
 * Created on 14 February 2016, 17:40
 */

#ifndef SENS4_H
#define	SENS4_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    unsigned int ReadSENS4();
    
    //Functions to read and write to the peripheral's buffer
    void WriteSENS4Buffer(unsigned int Data);
    void ReadSENS4Buffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENS4();
    int ClearSENS4Buffer();


#ifdef	__cplusplus
}
#endif

#endif	/* SENS4_H */

