/* 
 * File:   PeripheralTemplate.c
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#define BUFFER_LENGTH 256

int Buffer[BUFFER_LENGTH];
int Integral;
int Pointer;

//Function to read a value directly from the peripheral
int ReadPeripheral() {
    /*Code depends on peripheral*/
}

//Functions to read and write to the peripheral's buffer
int WritePeripheralBuffer(int Data) {
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
int* ReadPeripheralBuffer(int Count){
    /*
     * Returns a pointer to a buffer of the required size
     * 
     * I suggest this just organises the buffer and returns 
     * a pointer to the first value
     */
    //Reoorganise Buffer if count exceeds values remaining in memory
    if(Count>(BUFFER_LENGTH-Pointer)) {
        //Temporary Buffer
        int TempBuffer[BUFFER_LENGTH];

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
//Also includes a function to read from "special" value
//i.e. Integral for wheel encoders
int ReadPeripheralIntegral(){
    /*
     * Does what it says on the tin:
     * return Integral
     */
    return Integral;
}

int StartupPeripheral() {
    //Any startup code required by peripherals
    
}

//Functions to Initiate / Clear
int InitiatePeripheral() {
    /*
     * Ensure Buffer is full of zeros
     * 
     * Zero condition integral / special
     * 
     * Place pointer at the end of the buffer
     */
    //Ensure Buffer is full of zeros
    ClearBuffer();
    
    //Place pointer at end of buffer
    Pointer = BUFFER_LENGTH-1;
    
    //Zero integral
    Integral = 0;
    
    return 0;
}
int ClearPeripheralBuffer() {
    /*
     * Writes zeros into every cell of the buffer
     */
    for(int i=0; i<BUFFER_LENGTH; i++) Buffer[i] = 0;
    
    return 0;
}