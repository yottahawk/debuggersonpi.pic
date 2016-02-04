#include "spi.h"
#include <xc.h>
#include "StateMachine.h"

#define TIMEOUT 10000

void Initialise_SPI() {
    //Clear SPI2BUF register
    SPI2BUF = 0x0000;
    
    //Interrupts
    //Clear Flag
    IFS2bits.SPI2IF = 0; //Clear bit 1
    //Allow enable
    IEC2bits.SPI2IE = 1; //Set bit 1
    //Set priority to 0 
    IPC8bits.SPF2IP0 = 0;
    IPC8bits.SPI2IP1 = 0;
    IPC8bits.SPI2IP2 = 0;
    //Set interrupt to occur when receieve buffer has data
    SPI2STATbits.SISEL0 = 1;
    SPI2STATbits.SISEL1 = 0;
    SPI2STATbits.SISEL2 = 0;
   
    //Install interrupt to IVT
    int* IVT_LOC = 0x000056;
    *(IVT_LOC) = &SPI_Interrupt;
    
    //Setup SPI2CON1 for slave mode
    SPI2CON1bits.DISSDO = 0;  //Data out is controlled by module
    SPI2CON1bits.MODE16 = 0;  //8-bit data transfer
    SPI2CON1bits.CKE = 0;     //clocks data on idle to high 
    SPI2CON1bits.SSEN = 0;    //Slave select not used by modeul
    SPI2CON1bits.CKP  = 0;    //Clock is high when clock is high!
    SPI2CON1bits.MSTEN = 0;   //Slave mode
    
    //Setup SPI2CON2 for slave mode
    SPI2CON2bits.FRMEN = 0;   //Disable frame support
    SPI2CON2bits.SPIFSD = 1;  //Frame sync pulse set for slave (possibly unnecesary)
    
    SPI2CON1bits.SMP = 0;     //Slave mode
    SPI2STATbits.SPIROV = 0;  //Clear SPIROV bit
    SPI2CON2bits.SPIBEN = 1;  //Enable 8-byte buffer
    SPI2STATbits.SPIEN = 1;   //Enable SPI operation
}

//SPI Interrupt code
void SPI_Interrupt() {
    //timeout variable
    uint16_t n = 0;
    
    //When interrupt triggers, data has been received in Buffer.
    //First data in buffer is always command word!
    uint8_t command = (uint8_t) SPI2BUF;
    
    //compare command word to known states - if bit7 = 0, then is a state
    char IS_STATE = 0;
    if ((command & 0x80) > 0) {
        Next_State = (state_t) command; //if a state, change next state to it   
        SPI2BUF = 0xFE;                 //Send "DONE" to PI        
    }
    else {
        //if it isn't a state, its a the PI calling a function
        //if this is the case, we want to read the next two bytes in the buffer
        uint8_t data1, data2;
        
        n = 0;                                              //Set timeout to 0  
        while((SPI2STATbits.SRXMPT) & (++n < TIMEOUT)) {}   //Wait until receive buffer has data in
        //if (n >= TIMEOUT)                                       
        data1 = (uint8_t) SPI2BUF;

        n = 0;                                              //Set timeout to 0  
        while((SPI2STATbits.SRXMPT) & (++n < TIMEOUT)) {}   //Wait until receive buffer has data in
        //if (n >= TIMEOUT)
        data2 = (uint8_t) SPI2BUF;
        
        //combine the next 2 bytes to make a 16-bit word - this is the number of bytes to follow
        uint16_t byte_num = (((uint16_t) data1) << 8) | (((uint16_t) data2) & 0x00FF);
        
        //wait for the next BYTE_NUM bytes if any fail to come before timeout then the whole thing is null
        for(int i=0;i<byte_num;i++) {
            n = 0;
            while((SPI2STATbits.SRXMPT) & (++n < TIMEOUT)) {}
            //if(n >= TIMEOUT)
            spi_info.buffer[i] = SPI2BUF;
        }

        //Save the spi_info command and number of bytes
        spi_info.command = command;
        spi_info.number_of_bytes = byte_num;
    }
  
    //Ensure the receive buffer is empty;
    while(!SPI2STATbits.SRXMPT) {command = SPI2BUF;}
    
    //Clear interrupt flag
    IFS2bits.SPI2IF = 0;
}

//Discrete SPI function handler
void SPI_Function() {
    //This function is called if the PI wants to call certain functions
    //behaviour depends on the function the PI is calling
    switch ((command_t) spi_info.command) {
        case OPEN_GRABBER: {
            OpenGRABBER();          //Call appropriate function
            SPI2BUF = 0xFE;         //Write "DONE" signal to PI
        }
        case CLOSE_GRABBER: {
            CloseGRABBER();         //Call appropriate function
            SPI2BUF = 0xFE;         //Write "DONE" signal to PI
        }
    }
}