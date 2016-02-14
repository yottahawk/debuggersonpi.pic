/* 
 * File:   Sens6.h
 * Author: Luke
 *
 * Created on 14 February 2016, 17:41
 */

#ifndef SENS6_H
#define	SENS6_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    char ReadSENS6();
    
    //Functions to read and write to the peripheral's buffer
    int WriteSENS6Buffer(char Data);
    void ReadSENS6Buffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENS6();
    int ClearSENS6Buffer();


#ifdef	__cplusplus
}
#endif

#endif	/* SENS6_H */

