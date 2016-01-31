/* 
 * File:   SENS2Peripheral.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BUFFER_LENGTH 256
#define BIT_MASK 0x08
#define PIC_PORT PORTB
#define PIC_TRIS TRISB

#include <xc.h>
#include "Sens2Peripheral.h"

char Buffer[BUFFER_LENGTH];
int Pointer;

//Function to read a value directly from the peripheral
char ReadSENS2() {
    //Read B register and compare to bit mask
    int val = PIC_PORT & BIT_MASK;
    
    //if result of bit mask is non-zero, then peripheral is high
    //Otherwise peripheral is low
    if (val > 0) return 0x01;
    else return 0x00; 
}

//Functions to read and write to the peripheral's buffer
int WriteSENS2Buffer(char Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment Pointer 
    if(Pointer==0) Pointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else Pointer--; 
    
    //Insert data at new position
    Buffer[Pointer] = Data;
    
    //Integral Code?
}
char* ReadSENS2Buffer(int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-Pointer)) {
        //Temporary Buffer
        char TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=Pointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-Pointer] = Buffer[i];
        }
        for(int i=0;i<Pointer;i++){
            TempBuffer[Pointer+i] = Buffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) Buffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        Pointer = 0;
    };
    
    return &Buffer[Pointer];
}

int StartupSENS2() {
    // Ensure Data direction register is set to 1 (For 1nput)
    PIC_TRIS = PIC_TRIS | BIT_MASK;
}

//Functions to Initiate / Clear
int InitiateSENS2() {
    //Ensure Buffer is full of zeros
    ClearBuffer();
    
    //Place pointer at end of buffer
    Pointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENS2();
    
    return 0;
}
int ClearSENS2Buffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) Buffer[i] = 0;
    
    return 0;
}