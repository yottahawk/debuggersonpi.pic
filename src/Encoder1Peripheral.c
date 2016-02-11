/* 
 * File:   ENCODE1Peripheral.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

// WHEEL_ENC_1 is located on pin 42, on port D8. 

#define BUFFER_LENGTH 256
#define BIT_MASK 0x100         
#define PIC_PORT PORTD
#define PIC_TRIS TRISD

////////////////////////////////INCLUDES///////////////////////////////////////
#include <xc.h>

#include "Encoder1Peripheral.h"
// #include "Wheel1Peripheral.h"

////////////////////////////////GLOBAL VARIABLES////////////////////////////////

char Buffer[BUFFER_LENGTH];
int Pointer;

////////////////////////////////FUNCTIONS///////////////////////////////////////

//Function to read a value directly from the peripheral
char ReadENCODE1() {
    //Read B register and compare to bit mask
    int val = PIC_PORT & BIT_MASK;
    
    //if result of bit mask is non-zero, then peripheral is high
    //Otherwise peripheral is low
    if (val > 0) return 0x01;
    else return 0x00; 
}

////Functions to read and write to the peripheral's buffer
//int WriteENCODE1Buffer(char Data) {
//    /*
//     * Increments pointer (loops round if exceeds buffer size) 
//     * Inserts new value at position
//     */
//    char temp = Buffer[Pointer];
//    
//    //Increment Pointer 
//    if(Pointer==0) Pointer = BUFFER_LENGTH-1; //Loop pointer if exceeds buffer length
//    else Pointer--; 
//    
//    //Insert data at new position
//    Buffer[Pointer] = Data;
//    
//    //Integral Code - only changes if the current value is different to
//    //the previous value. Increments if wheel is going forwards, decrements if
//    //wheel is going backwards
//    if (temp != Buffer[Pointer]) {
//        if (ReadWHEEL1()) Integral++;
//        else Integral--;
//    }
//}
//char* ReadENCODE1Buffer(int Count){
//    /*
//     * Returns a pointer to a buffer of the required size
//     * 
//     * I suggest this just organises the buffer and returns 
//     * a pointer to the first value
//     */
//    //Reoorganise Buffer if count exceeds values remaining in memory
//    if(Count>(BUFFER_LENGTH-Pointer)) {
//        //Temporary Buffer
//        char TempBuffer[BUFFER_LENGTH];
//
//        //Fill temporarybuffer with values from Buffer
//        for(int i=Pointer;i<BUFFER_LENGTH;i++){
//            TempBuffer[i-Pointer] = Buffer[i];
//        }
//        for(int i=0;i<Pointer;i++){
//            TempBuffer[Pointer+i] = Buffer[i];
//        }
//        
//        //Copy temporary buffer to buffer
//        for(int i=0;i<BUFFER_LENGTH;i++) Buffer[i] = TempBuffer[i];
//        
//        //Reset pointer to start of buffer
//        Pointer = 0;
//    };
//    
//    return &Buffer[Pointer];
//}
//
//int ReadENCODE1Integral() {
//    return Integral;
//}
//int ResetENCODE1Integral() {
//    Integral = 0;
//}
//
//int StartupENCODE1() {
//    // Ensure Data direction register is set to 1 (For 1nput)
//    PIC_TRIS = PIC_TRIS | BIT_MASK;
//}
//
////Functions to Initiate / Clear
//int InitiateENCODE1() {
//    //Ensure Buffer is full of zeros
//    ClearBuffer();
//    
//    //Place pointer at end of buffer
//    Pointer = BUFFER_LENGTH-1;
//    
//    //Initiate data direction bits
//    StartupENCODE1();
//    
//    return 0;
//}
//int ClearENCODE1Buffer() {
//    /*
//     * Writes zeros into every cell of the buffer
//     */
//    for(int i=0; i<BUFFER_LENGTH; i++) Buffer[i] = 0;
//    
//    return 0;
//}