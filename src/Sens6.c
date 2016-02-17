/* 
 * File:   Sens6.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BUFFER_LENGTH 256

#include <xc.h>
#include "Sens6.h"

unsigned int SENS6Buffer[BUFFER_LENGTH];
unsigned int SENS6Pointer;

//Function to read a value directly from the peripheral
unsigned int ReadSENS6() {
    return 0;
}

//Functions to read and write to the peripheral's buffer
void WriteSENS6Buffer(unsigned int Data) {
    /*
     * Increments pointer (loops round if exceeds buffer size) 
     * Inserts new value at position
     */
    //Increment SENS6Pointer 
    if(SENS6Pointer==0) SENS6Pointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
    else SENS6Pointer--; 
    
    //Insert data at new position
    SENS6Buffer[SENS6Pointer] = Data;
    
    //Integral Code?
}
void ReadSENS6Buffer(unsigned int* Dest, int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-SENS6Pointer)) {
        //Temporary Buffer
        unsigned int TempBuffer[BUFFER_LENGTH];

        //Fill temporarybuffer with values from Buffer
        for(int i=SENS6Pointer;i<BUFFER_LENGTH;i++){
            TempBuffer[i-SENS6Pointer] = SENS6Buffer[i];
        }
        for(int i=0;i<SENS6Pointer;i++){
            TempBuffer[SENS6Pointer+i] = SENS6Buffer[i];
        }
        
        //Copy temporary buffer to buffer
        for(int i=0;i<BUFFER_LENGTH;i++) SENS6Buffer[i] = TempBuffer[i];
        
        //Reset pointer to start of buffer
        SENS6Pointer = 0;
    };
    
    Dest = &SENS6Buffer[SENS6Pointer];
}

int StartupSENS6() {
    return 0;
}

//Functions to Initiate / Clear
int InitiateSENS6() {
    //Ensure Buffer is full of zeros
    ClearSENS6Buffer();
    
    //Place pointer at end of buffer
    SENS6Pointer = BUFFER_LENGTH-1;
    
    //Initiate data direction bits
    StartupSENS6();
    
    return 0;
}
int ClearSENS6Buffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) SENS6Buffer[i] = 0;
    
    return 0;
}
