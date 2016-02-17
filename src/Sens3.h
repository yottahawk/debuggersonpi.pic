/* 
 * File:   Sens2.h
 * Author: Luke
 *
 * Created on 14 February 2016, 17:39
 */

#ifndef SENS2_H
#define	SENS2_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    unsigned int ReadSENS3();
    
    //Functions to read and write to the peripheral's buffer
    void WriteSENS3Buffer(unsigned int Data);
    void ReadSENS3Buffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENS3();
    int ClearSENS3Buffer();


#ifdef	__cplusplus
}
#endif

#endif	/* SENS2_H */

