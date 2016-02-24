/* 
 * File:   SENSCPeripheral.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BUFFER_LENGTH 256
#define BIT_MASK 0x1000;

#include <xc.h>
#include "SensCPeripheral.h"

unsigned int SENSCBuffer[BUFFER_LENGTH];
unsigned int SENSCPointer;

//Function to read a value directly from the peripheral
unsigned int ReadSENSC() {
    //Read B register and compare to bit mask
    int val = PORTB & BIT_MASK;
    
    //if result of bit mask is non-zero, then peripheral is high
    //Otherwise peripheral is low
    if (val > 0) return 0x01;
    else return 0x00; 
}

//Functions to read and write to the peripheral's buffer
void WriteSENSCBuffer(unsigned int Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment SENSCPointer 
    if(SENSCPointer==0) SENSCPointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else SENSCPointer--; 
    
    //Insert data at new position
    SENSCBuffer[SENSCPointer] = Data;
    
    //Integral Code?
}
void ReadSENSCBuffer(unsigned int* Dest, int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-SENSCPointer)) {
        //Temporary Buffer
        unsigned int TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=SENSCPointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-SENSCPointer] = SENSCBuffer[i];
        }
        for(int i=0;i<SENSCPointer;i++){
            TempBuffer[SENSCPointer+i] = SENSCBuffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) SENSCBuffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        SENSCPointer = 0;
    };
    
    Dest = &SENSCBuffer[SENSCPointer];
}

void StartupSENSC() {
    // Ensure Data direction register is set to 1 (For 1nput)
    TRISB = TRISB | BIT_MASK;
}

//Functions to Initiate / Clear
int InitiateSENSC() {
    //Ensure Buffer is full of zeros
    ClearSENSCBuffer();
    
    //Place pointer at end of buffer
    SENSCPointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENSC();
    
    return 0;
}
int ClearSENSCBuffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) SENSCBuffer[i] = 0;
    
    return 0;
}