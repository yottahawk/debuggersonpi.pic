/* 
 * File:   Sens5.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BUFFER_LENGTH 256

#include <xc.h>
#include "Sens5.h"

unsigned int SENS5Buffer[BUFFER_LENGTH];
unsigned int SENS5Pointer;

//Function to read a value directly from the peripheral
unsigned int ReadSENS5() {
    return 0;
}

//Functions to read and write to the peripheral's buffer
void WriteSENS5Buffer(unsigned int Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment SENS5Pointer 
    if(SENS5Pointer==0) SENS5Pointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else SENS5Pointer--; 
    
    //Insert data at new position
    SENS5Buffer[SENS5Pointer] = Data;
    
    //Integral Code?
}
void ReadSENS5Buffer(unsigned int* Dest, int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-SENS5Pointer)) {
        //Temporary Buffer
        unsigned int TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=SENS5Pointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-SENS5Pointer] = SENS5Buffer[i];
        }
        for(int i=0;i<SENS5Pointer;i++){
            TempBuffer[SENS5Pointer+i] = SENS5Buffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) SENS5Buffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        SENS5Pointer = 0;
    };
    
    Dest = &SENS5Buffer[SENS5Pointer];
}

int StartupSENS5() {
    return 0;
}

//Functions to Initiate / Clear
int InitiateSENS5() {
    //Ensure Buffer is full of zeros
    ClearSENS5Buffer();
    
    //Place pointer at end of buffer
    SENS5Pointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENS5();
    
    return 0;
}
int ClearSENS5Buffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) SENS5Buffer[i] = 0;
    
    return 0;
}
