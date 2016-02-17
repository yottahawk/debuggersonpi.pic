/* 
 * File:   SENS1Peripheral.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BUFFER_LENGTH 256
#define BIT_MASK 0x10
#define PIC_PORT PORTB
#define PIC_TRIS TRISB

#include <xc.h>
#include "Sens1Peripheral.h"

unsigned int SENS1Buffer[BUFFER_LENGTH];
unsigned int SENS1Pointer;

//Function to read a value directly from the peripheral
unsigned int ReadSENS1() {
    //Read B register and compare to bit mask
    int val = PIC_PORT & BIT_MASK;
    
    //if result of bit mask is non-zero, then peripheral is high
    //Otherwise peripheral is low
    if (val > 0) return 0x01;
    else return 0x00; 
}

//Functions to read and write to the peripheral's buffer
void WriteSENS1Buffer(unsigned int Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment SENS1Pointer 
    if(SENS1Pointer==0) SENS1Pointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else SENS1Pointer--; 
    
    //Insert data at new position
    SENS1Buffer[SENS1Pointer] = Data;
    
    //Integral Code?
}
void ReadSENS1Buffer(unsigned int* Dest, int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-SENS1Pointer)) {
        //Temporary Buffer
        unsigned int TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=SENS1Pointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-SENS1Pointer] = SENS1Buffer[i];
        }
        for(int i=0;i<SENS1Pointer;i++){
            TempBuffer[SENS1Pointer+i] = SENS1Buffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) SENS1Buffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        SENS1Pointer = 0;
    };
    
    Dest = &SENS1Buffer[SENS1Pointer];
}

void StartupSENS1() {
    // Ensure Data direction register is set to 1 (For 1nput)
    PIC_TRIS = PIC_TRIS | BIT_MASK;
}

//Functions to Initiate / Clear
int InitiateSENS1() {
    //Ensure Buffer is full of zeros
    ClearSENS1Buffer();
    
    //Place pointer at end of buffer
    SENS1Pointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENS1();
    
    return 0;
}
int ClearSENS1Buffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) SENS1Buffer[i] = 0;
    
    return 0;
}