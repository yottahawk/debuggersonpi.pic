/* 
 * File:   SensFRONT.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BUFFER_LENGTH 256
#define BIT_MASK 0x0004
#define PIC_PORT PORTB
#define PIC_TRIS TRISB

#include <xc.h>
#include "SensFRONT.h"

unsigned int SENSFBuffer[BUFFER_LENGTH];
unsigned int SENSFPointer;

//Function to read a value directly from the peripheral
unsigned int ReadSENSF() {
    //Read B register and compare to bit mask
    int val = PIC_PORT & BIT_MASK;
    
    //if result of bit mask is non-zero, then peripheral is high
    //Otherwise peripheral is low
    if (val > 0) return 0x01;
    else return 0x00; 
}

//Functions to read and write to the peripheral's buffer
void WriteSENSFBuffer(unsigned int Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment SENSFPointer 
    if(SENSFPointer==0) SENSFPointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else SENSFPointer--; 
    
    //Insert data at new position
    SENSFBuffer[SENSFPointer] = Data;
    
    //Integral Code?
}
void ReadSENSFBuffer(unsigned int* Dest, int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-SENSFPointer)) {
        //Temporary Buffer
        unsigned int TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=SENSFPointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-SENSFPointer] = SENSFBuffer[i];
        }
        for(int i=0;i<SENSFPointer;i++){
            TempBuffer[SENSFPointer+i] = SENSFBuffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) SENSFBuffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        SENSFPointer = 0;
    };
    
    Dest = &SENSFBuffer[SENSFPointer];
}

int StartupSENSF() {
    // Ensure Data direction register is set to 1 (For 1nput)
    PIC_TRIS = PIC_TRIS | BIT_MASK;
    return 0;
}

//Functions to Initiate / Clear
int InitiateSENSF() {
    //Ensure Buffer is full of zeros
    ClearSENSFBuffer();
    
    //Place pointer at end of buffer
    SENSFPointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENSF();
    
    return 0;
}
int ClearSENSFBuffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) SENSFBuffer[i] = 0;
    
    return 0;
}
