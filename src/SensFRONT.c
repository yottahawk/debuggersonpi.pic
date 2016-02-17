/* 
 * File:   SensFRONT.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BUFFER_LENGTH 256

#include <xc.h>
#include "SensFRONT.h"

unsigned int SENSFRONTBuffer[BUFFER_LENGTH];
unsigned int SENSFRONTPointer;

//Function to read a value directly from the peripheral
unsigned int ReadSENSFRONT() {
    return 0;
}

//Functions to read and write to the peripheral's buffer
void WriteSENSFRONTBuffer(unsigned int Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment SENSFRONTPointer 
    if(SENSFRONTPointer==0) SENSFRONTPointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else SENSFRONTPointer--; 
    
    //Insert data at new position
    SENSFRONTBuffer[SENSFRONTPointer] = Data;
    
    //Integral Code?
}
void ReadSENSFRONTBuffer(unsigned int* Dest, int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-SENSFRONTPointer)) {
        //Temporary Buffer
        unsigned int TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=SENSFRONTPointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-SENSFRONTPointer] = SENSFRONTBuffer[i];
        }
        for(int i=0;i<SENSFRONTPointer;i++){
            TempBuffer[SENSFRONTPointer+i] = SENSFRONTBuffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) SENSFRONTBuffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        SENSFRONTPointer = 0;
    };
    
    Dest = &SENSFRONTBuffer[SENSFRONTPointer];
}

int StartupSENSFRONT() {
    return 0;
}

//Functions to Initiate / Clear
int InitiateSENSFRONT() {
    //Ensure Buffer is full of zeros
    ClearSENSFRONTBuffer();
    
    //Place pointer at end of buffer
    SENSFRONTPointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENSFRONT();
    
    return 0;
}
int ClearSENSFRONTBuffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) SENSFRONTBuffer[i] = 0;
    
    return 0;
}
