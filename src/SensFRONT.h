/* 
 * File:   SensFRONT.h
 * Author: Luke
 *
 * Created on 14 February 2016, 17:43
 */

#ifndef SENSFRONT_H
#define	SENSFRONT_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    char ReadSENSFRONT();
    
    //Functions to read and write to the peripheral's buffer
    int WriteSENSFRONTBuffer(char Data);
    void ReadSENSFRONTBuffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENSFRONT();
    int ClearSENSFRONTBuffer();


#ifdef	__cplusplus
}
#endif

#endif	/* SENSFRONT_H */

