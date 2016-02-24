/* 
 * File:   SENSRPeripheral.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BIT_MASK 0x08
#define PIC_PORT PORTB
#define PIC_TRIS TRISB

#include <xc.h>
#include "SensRPeripheral.h"

unsigned int SENSRBuffer[BUFFER_LENGTH];
unsigned int SENSRPointer;

//Function to read a value directly from the peripheral
unsigned int ReadSENSR() {
    //Read B register and compare to bit mask
    int val = PIC_PORT & BIT_MASK;
    
    //if result of bit mask is non-zero, then peripheral is high
    //Otherwise peripheral is low
    if (val > 0) return 0x01;
    else return 0x00; 
}

//Functions to read and write to the peripheral's buffer
void WriteSENSRBuffer(unsigned int Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment SENSRPointer 
    if(SENSRPointer==0) SENSRPointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else SENSRPointer--; 
    
    //Insert data at new position
    SENSRBuffer[SENSRPointer] = Data;
    
    //Integral Code?
}
void ReadSENSRBuffer(unsigned int* Dest, int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-SENSRPointer)) {
        //Temporary Buffer
        unsigned int TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=SENSRPointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-SENSRPointer] = SENSRBuffer[i];
        }
        for(int i=0;i<SENSRPointer;i++){
            TempBuffer[SENSRPointer+i] = SENSRBuffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) SENSRBuffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        SENSRPointer = 0;
    };
    
    Dest = &SENSRBuffer[SENSRPointer];
}

void StartupSENSR() {
    // Ensure Data direction register is set to 1 (For 1nput)
    PIC_TRIS = PIC_TRIS | BIT_MASK;
}

//Functions to Initiate / Clear
int InitiateSENSR() {
    //Ensure Buffer is full of zeros
    ClearSENSRBuffer();
    
    //Place pointer at end of buffer
    SENSRPointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENSR();
    
    return 0;
}
int ClearSENSRBuffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) SENSRBuffer[i] = 0;
    
    return 0;
}