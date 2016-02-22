/* 
 * File:   ENCODE1Peripheral.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

// WHEEL_ENC_1 is located on port D8 (pin 42)
// WHEEL_ENC_2 is located on port D9 (pin 43)

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "wheelEncoders.h"

#include "math.h"

/////////////////////////////////////DEFINES////////////////////////////////////

#define WHEELDIAMETER_MM 70
#define PI 3.14
#define WHEELCIRCUMFERENCE_MM 219.8
#define ENCODERSPOKES 32
#define TRAVELPERSPOKE_MM 6.9

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

// Counter registers to store the current count.
int GLOBAL_enc1_count = 0;
int GLOBAL_enc2_count = 0;

// Store current stop condition for count. DO NOT ACCESS DIRECTLY, use access method.
int GLOBAL_enc1_limit = 0;
int GLOBAL_enc2_limit = 0;
int GLOBAL_encAverage_limit = 0;

// Global flags for counter complete
int GLOBAL_enc1_complete = 0;
int GLOBAL_enc2_complete = 0;
int GLOBAL_encAverage_complete = 0;

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

void enc1_setupInterrupt()
{
    /* 
     * Setup the interrupts used to increment the count register for Encoder 1.
     * Encoder 1 uses External Interrupt 1 (INT1) 
     * 
     * Interrupt uses default handler _INT1Interrupt.
     * 
     * 
     */
    
    INTCON2bits.INT1EP = 0;         // Trigger on negative edge
    IFS1bits.INT1IF = 0;            // Set INT1 flag to 0.
    
    IEC1bits.INT1IE = 1;            // Enable INT1 interrupt 
}
void enc2_setupInterrupt()
{
    /* 
     * Setup the interrupts used to increment the count register for Encoder 2.
     * Encoder 2 uses External Interrupt 2 (INT2) 
     * 
     * Interrupt uses default handler _INT2Interrupt.
     * 
     * 
     */
    
    INTCON2bits.INT2EP = 0;         // Trigger on negative edge
    IFS1bits.INT2IF = 0;            // Set INT2 flag to 0.
    
    IEC1bits.INT2IE = 1;            // Enable INT1 interrupt 
}

int enc1_readValue() 
{
    //Function to read a value directly from the peripheral
    return PORTDbits.RD8;
}
int enc2_readValue() 
{
    //Function to read a value directly from the peripheral
    return PORTDbits.RD8;
}

void enc1_resetCounter()
{
    /*
     * Resets the value of the encoder 1 counter to 0. 
     */
    // Count is no complete, reset flag
    GLOBAL_enc1_complete = 0;
    
    GLOBAL_enc1_count = 0;
}
void enc2_resetCounter()
{
    /*
     * Resets the value of the encoder 1 counter to 0. 
     */
    // Count is no complete, reset flag
    GLOBAL_enc2_complete = 0;
    
    GLOBAL_enc2_count = 0;
}

int enc1_Store()
{
    /*
     * Returns the last value of the counter as an int. 
     */
    return GLOBAL_enc1_count; // Store current value before it is overwritten
}

int enc2_Store()
{
    /*
     * Returns the last value of the counter as an int. 
     */
    return GLOBAL_enc2_count; // Store current value before it is overwritten
}

int enc1_resetAndStore()
{
    /*
     * Returns the last value of the counter as an int.
     * Resets the value of the encoder 1 counter to 0.  
     */
    // Count is no complete, reset flag
    GLOBAL_enc1_complete = 0;
    
    int temp = GLOBAL_enc1_count; // Store current value before it is overwritten
    GLOBAL_enc1_count = 0;
    
    return temp;
}
int enc2_resetAndStore()
{
    /*
     * Returns the last value of the counter as an int.
     * Resets the value of the encoder 1 counter to 0.  
     */
    // Count is no complete, reset flag
    GLOBAL_enc2_complete = 0;
    
    int temp = GLOBAL_enc2_count; // Store current value before it is overwritten
    
    GLOBAL_enc2_count = 0;
    
    return temp;
}

void enc1_writeCounterLimit(int limit)
{
    /*
     * Writes a new value to the counter limit register for encoder 1.
     */
    // Count is no longer complete, reset flag
    GLOBAL_enc1_complete = 0;
    
    GLOBAL_enc1_limit = limit;
}
void enc2_writeCounterLimit(int limit)
{
    /*
     * Writes a new value to the counter limit register for encoder 1.
     */
    // Count is no complete, reset flag
    GLOBAL_enc2_complete = 0;
    
    GLOBAL_enc2_limit = limit;
}
void encAvg_writeCounterLimit(int limit)
{
    /*
     * Writes a new value to the counter limit register for the average
     * of encoder 1 and 2.
     */
    // Count is no complete, reset flag
    GLOBAL_encAverage_complete = 0;
    
    GLOBAL_encAverage_limit = limit;
}

void enc1_writeCounterLimitDistance(int distance_mm)
{
    /*
     * 
     * Calculates the number of counts to register that represent a certain 
     * distance of wheel rotation.
     * 
     * Writes a new value to the counter limit register for encoder 1.
     */
    
    // Calculate the number of counts as a float.
    float requiredCounts_float = (float) distance_mm / (float) TRAVELPERSPOKE_MM;
   
    // Cast answer as an int
    int roundedLimit = (int) requiredCounts_float;
    
    // Write answer to the global counter limit register
    enc1_writeCounterLimit(roundedLimit);
}
void enc2_writeCounterLimitDistance(int distance_mm)
{
    /*
     * 
     * Calculates the number of counts to register that represent a certain 
     * distance of wheel rotation.
     * 
     * Writes a new value to the counter limit register for encoder 2.
     */
    
    // Calculate the number of counts as a float.
    float requiredCounts_float = (float) distance_mm / (float) TRAVELPERSPOKE_MM;
   
    // Cast answer as an int
    int roundedLimit = (int) requiredCounts_float;
    
    // Write answer to the global counter limit register
    enc2_writeCounterLimit(roundedLimit);
}
void encAvg_writeCounterLimitDistance(int distance_mm)
{
    /*
     * 
     * Calculates the number of counts to register that represent a certain 
     * distance of wheel rotation.
     * 
     * Writes a new value to the counter limit register for the average of encoders
     * 1 and 2.
     */
    
    // Calculate the number of counts as a float.
    float requiredCounts_float = (float) distance_mm / (float) TRAVELPERSPOKE_MM;
   
    // Cast answer as an int
    int roundedLimit = (int) requiredCounts_float;
    
    // Write answer to the global counter limit register
    encAvg_writeCounterLimit(roundedLimit);
}

void enc_flagCounterComplete()
{
    /*
     * Set flags when encoder count registers is equal or greater than limit register.
     * 
     * Flag should be reset when counters are reset / new limits are written.
     */
    
    if (GLOBAL_enc1_count >= GLOBAL_enc1_limit)
    {
        // Count is complete, set flag
        GLOBAL_enc1_complete = 1;
        // Flag should now be read by another function to branch/jump/change state.
    }
    else{}
        
    if (GLOBAL_enc2_count >= GLOBAL_enc2_limit)
    {
        // Count is complete, set flag
        GLOBAL_enc2_complete = 1;
        // Flag should now be read by another function to branch/jump/change state.
    }
    else{}
    
    int average = (GLOBAL_enc1_limit + GLOBAL_enc2_limit) / 2;
    
    if (average >= GLOBAL_encAverage_limit)
    {
        // Count is complete, set flag
        GLOBAL_encAverage_complete = 1;
        // Flag should now be read by another function to branch/jump/change state.
    }
    else{}
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