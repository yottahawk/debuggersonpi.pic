/* 
 * File:   SensFRONT.h
 * Author: Luke
 *
 * Created on 14 February 2016, 17:43
 */

#ifndef SENSF_H
#define	SENSF_H

#ifdef	__cplusplus
extern "C" {
#endif

    //Function to read a value directly from the peripheral
    unsigned int ReadSENSF();
    
    //Functions to read and write to the peripheral's buffer
    void WriteSENSFBuffer(unsigned int Data);
    void ReadSENSFBuffer(unsigned int* Dest, int Count);
    
    //Functions to Initiate / Clear
    int InitiateSENSF();
    int ClearSENSFBuffer();


#ifdef	__cplusplus
}
#endif

#endif	/* SENSF_H */

