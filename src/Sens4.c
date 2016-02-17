/* 
 * File:   Sens4.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BUFFER_LENGTH 256

#include <xc.h>
#include "Sens4.h"

unsigned int SENS4Buffer[BUFFER_LENGTH];
unsigned int SENS4Pointer;

//Function to read a value directly from the peripheral
unsigned int ReadSENS4() {
    return 0;
}

//Functions to read and write to the peripheral's buffer
void WriteSENS4Buffer(unsigned int Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment Pointer 
    if(SENS4Pointer==0) SENS4Pointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else SENS4Pointer--; 
    
    //Insert data at new position
    SENS4Buffer[SENS4Pointer] = Data;
    
    //Integral Code?
}
void ReadSENS4Buffer(unsigned int* Dest, int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-SENS4Pointer)) {
        //Temporary Buffer
        unsigned int TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=SENS4Pointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-SENS4Pointer] = SENS4Buffer[i];
        }
        for(int i=0;i<SENS4Pointer;i++){
            TempBuffer[SENS4Pointer+i] = SENS4Buffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) SENS4Buffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        SENS4Pointer = 0;
    };
    
    Dest = &SENS4Buffer[SENS4Pointer];
}

int StartupSENS4() {
    return 0;
}

//Functions to Initiate / Clear
int InitiateSENS4() {
    //Ensure Buffer is full of zeros
    ClearSENS4Buffer();
    
    //Place pointer at end of buffer
    SENS4Pointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENS4();
    
    return 0;
}
int ClearSENS4Buffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) SENS4Buffer[i] = 0;
    
    return 0;
}
