/* 
 * File:   SENSCUBEPeripheral.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BUFFER_LENGTH 256
#define BIT_MASK 0x20;

#include <xc.h>
#include "SensCubePeripheral.h"

unsigned int SENSCUBEBuffer[BUFFER_LENGTH];
unsigned int SENSCUBEPointer;

//Function to read a value directly from the peripheral
unsigned int ReadSENSCUBE() {
    //Read B register and compare to bit mask
    int val = PORTB & BIT_MASK;
    
    //if result of bit mask is non-zero, then peripheral is high
    //Otherwise peripheral is low
    if (val > 0) return 0x01;
    else return 0x00; 
}

//Functions to read and write to the peripheral's buffer
void WriteSENSCUBEBuffer(unsigned int Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment SENSCUBEPointer 
    if(SENSCUBEPointer==0) SENSCUBEPointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else SENSCUBEPointer--; 
    
    //Insert data at new position
    SENSCUBEBuffer[SENSCUBEPointer] = Data;
    
    //Integral Code?
}
void ReadSENSCUBEBuffer(unsigned int* Dest, int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-SENSCUBEPointer)) {
        //Temporary Buffer
        unsigned int TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=SENSCUBEPointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-SENSCUBEPointer] = SENSCUBEBuffer[i];
        }
        for(int i=0;i<SENSCUBEPointer;i++){
            TempBuffer[SENSCUBEPointer+i] = SENSCUBEBuffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) SENSCUBEBuffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        SENSCUBEPointer = 0;
    };
    
    Dest = &SENSCUBEBuffer[SENSCUBEPointer];
}

void StartupSENSCUBE() {
    // Ensure Data direction register is set to 1 (For 1nput)
    TRISB = TRISB | BIT_MASK;
}

//Functions to Initiate / Clear
int InitiateSENSCUBE() {
    //Ensure Buffer is full of zeros
    ClearSENSCUBEBuffer();
    
    //Place pointer at end of buffer
    SENSCUBEPointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENSCUBE();
    
    return 0;
}
int ClearSENSCUBEBuffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) SENSCUBEBuffer[i] = 0;
    
    return 0;
}