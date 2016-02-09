#include "spi.h"
#include <xc.h>
#include "StateMachine.h"

#define TIMEOUT 10000

const uint8_t DONE = 0xFE;

//Function to write to spi link
void Write_SPI(uint8_t* buffer, uint16_t length) {
    //For each byte in the buffer...
    for(int i=0;i<length;i++) {
        while(SPI2STATbits.SPITBF) {} //wait until there is space in the buffer
        SPI2BUF = buffer[i];
    }
}

void SPI_PSNS(uint8_t Sensor) {
    //Get data
    uint8_t value = 0;
    if(Sensor==0)       value = ReadPHOTOSENSE1();
    else if(Sensor==1)  value = ReadPHOTOSENSE2();
    else if(Sensor==2)  value = ReadPHOTOSENSE3();
    else if(Sensor==3)  value = ReadPHOTOSENSE4();
    else if(Sensor==4)  value = ReadPHOTOSENSE5();
    else                value = ReadPHOTOSENSE6();

    //Return data to PI
    Write_SPI(&value, 1);
    Write_SPI(&DONE, 1);
}

void SPI_COMP() {
        //Get data
    uint16_t direction = ReadCOMPASS();

    //separate into msb and lsb parts
    uint8_t msb = (uint8_t) ((direction & 0xFF00) >> 8);
    uint8_t lsb = (uint8_t) (direction);

    //Return data to PI
    Write_SPI(&msb, 1);
    Write_SPI(&lsb, 1);
    Write_SPI(&DONE, 1);
}

void SPI_ECDR(uint8_t Mode) {
    if(Mode <= 1) {             //If mode is read buffer
        //need to read a certain number of bytes
        uint16_t n = 0;
        n = ((uint16_t) spi_info.buffer[0] << 8) & 0xFF00;
        n = n | (((uint16_t) spi_info.buffer[1]) & 0x00FF);     
        
        //Get Data
        uint8_t* encoder_data = 0;
        if(Mode == 0) ReadENCODE1Buffer(n);
        else          ReadENCODE2Buffer(n);
    
        //Return data to PI
        Write_SPI(&encoder_data[0], n);
    }
    else {
        //Get data
        uint16_t integral = 0;
        if(Mode==2) integral = ReadENCODE1Integral();
        else        integral = ReadENCODE2Integral();

        //separate into msb and lsb parts
        uint8_t msb = (uint8_t) ((integral & 0xFF00) >> 8);
        uint8_t lsb = (uint8_t) (integral);

        //Return data to PI
        Write_SPI(&msb, 1);
        Write_SPI(&lsb, 1);
    }
    
    //Write DONE to end transaction
    Write_SPI(&DONE, 1);
}

void SPI_MOTOR(uint8_t Mode) {
    if(Mode<=1) {               //If mode is writing
        //Build correct structure
        uint16_t motor_speed = 0;
        motor_speed = ((uint16_t) spi_info.buffer[0] << 8) & 0xFF00;
        motor_speed = motor_speed | (((uint16_t) spi_info.buffer[1]) & 0x00FF);
        //send via spi
        if(Mode==0)     WriteMOTOR1(motor_speed);
        else if(Mode==1)WriteMOTOR2(motor_speed);
    } else {                    //if mode is reading
        uint16_t motor_speed = 0;
        if(Mode==2) motor_speed = ReadMOTOR1();
        else        motor_speed = ReadMOTOR2();
        Write_SPI(&motor_speed, 1);
    }
    
    //Write done to spi to finish transaction
    Write_SPI(&DONE,1);
}

void SPI_GRABBER(uint8_t Mode) {
    //placeholder variable for readgrabber
    uint8_t val=0;
    
    //Call appropriate grabber function
    if(Mode==0)     OpenGRABBER();          //Call appropriate function
    else if(Mode==1)CloseGRABBER();
    else      val = ReadGrabber();
    
    //Write val to SPI if readgrabber has been called
    if(val != 0) Write_SPI(&val,1);
    
    Write_SPI(&DONE, 1);        //Write "DONE" signal to PI   
}

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
            SPI_GRABBER(0);
            break;}
        case CLOSE_GRABBER: {
            SPI_GRABBER(1);
            break;}
        case READ_GRABBER: {
            SPI_GRABBER(2);
            break;}
        case WRITE_MOTOR1: {
            SPI_MOTOR(0);
            break;}
        case WRITE_MOTOR2: {
            SPI_MOTOR(1);
            break;}
        case READ_MOTOR1: {
            SPI_MOTOR(2);
            break;}
        case READ_MOTOR2: {
            SPI_MOTOR(3);
            break;}
        case READ_ECDR1: {
            SPI_ECDR(0);
            break;}
        case READ_ECDR2: {
            SPI_ECDR(1);
            break;}
        case READ_ECDR1_INT: {
            SPI_ECDR(2);
            break;}
        case READ_ECDR2_INT: {
            SPI_ECDR(3);
            break;}
        case READ_COMP: {
            SPI_COMP();
            break;}
        case READ_PSNS1: {
            SPI_PSNS(0);
            break;}
        case READ_PSNS2: {
            SPI_PSNS(1);
            break;}
        case READ_PSNS3: {
            SPI_PSNS(2);
            break;}
        case READ_PSNS4: {
            SPI_PSNS(3);
            break;}
        case READ_PSNS5: {
            SPI_PSNS(4);
            break;}
        case READ_PSNS6: {
            SPI_PSNS(5);
            break;}
        default:    //do nothing in default case
    }
    
    //clear spi_info structure
    spi_info.command = 0;
    spi_info.number_of_bytes = 0;
    for(int i=0;i<256;i++) spi_info.buffer[i] = 0;
}
