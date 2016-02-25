/* 
 * File:   SENSLPeripheral.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BIT_MASK 0x2000
#define PIC_PORT PORTB
#define PIC_TRIS TRISB

#include <xc.h>
#include "SensLPeripheral.h"

unsigned int SENSLBuffer[BUFFER_LENGTH];
unsigned int SENSLPointer;

//Function to read a value directly from the peripheral
unsigned int ReadSENSL() {
    //Read B register and compare to bit mask
    int val = PIC_PORT & BIT_MASK;
    
    //if result of bit mask is non-zero, then peripheral is high
    //Otherwise peripheral is low
    if (val > 0) return 0x01;
    else return 0x00; 
}

//Functions to read and write to the peripheral's buffer
void WriteSENSLBuffer(unsigned int Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment SENSLPointer 
    if(SENSLPointer==0) SENSLPointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else SENSLPointer--; 
    
    //Insert data at new position
    SENSLBuffer[SENSLPointer] = Data;
    
    //Integral Code?
}
void ReadSENSLBuffer(unsigned int* Dest, int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-SENSLPointer)) {
        //Temporary Buffer
        unsigned int TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=SENSLPointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-SENSLPointer] = SENSLBuffer[i];
        }
        for(int i=0;i<SENSLPointer;i++){
            TempBuffer[SENSLPointer+i] = SENSLBuffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) SENSLBuffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        SENSLPointer = 0;
    };
    
    Dest = &SENSLBuffer[SENSLPointer];
}

void StartupSENSL() {
    // Ensure Data direction register is set to 1 (For 1nput)
    PIC_TRIS = PIC_TRIS | BIT_MASK;
}

//Functions to Initiate / Clear
int InitiateSENSL() {
    //Ensure Buffer is full of zeros
    ClearSENSLBuffer();
    
    //Place pointer at end of buffer
    SENSLPointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENSL();
    
    return 0;
}
int ClearSENSLBuffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) SENSLBuffer[i] = 0;
    
    return 0;
}