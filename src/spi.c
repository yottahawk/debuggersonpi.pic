#include "spi.h"
#include <xc.h>
#include "StateMachine.h"
#include "led.h"
#include "grabber.h"
#include "Sens1Peripheral.h"
#include "Sens2Peripheral.h"
#include "Sens3.h"
#include "Sens4.h"
#include "Sens5.h"
#include "Sens6.h"
#include "SensCubePeripheral.h"
#include "SensFRONT.h"
#include "compass.h"
#include "wheelEncoders.h"
#include "motors.h"

#define TIMEOUT 10000

//Function to write to spi link
void Write_SPI(unsigned int* buffer, unsigned int length) {
    //For each byte in the buffer...
    for(int i=0;i<length;i++) {
        while(SPI2STATbits.SPITBF) {} //wait until there is space in the buffer
        SPI2BUF = buffer[i];
    }
}

void SPI_PSNS(uint8_t Sensor, unsigned int Length, unsigned int Clear) {
    //Error code (to prevent reading longer than buffer)
    uint8_t error = 0;
    
    //Buffer to send data from
    unsigned int* Buffer; 
    
    //Get data
    if(Sensor==0)      ReadSENS1Buffer(Buffer, Length);
    else if(Sensor==1) ReadSENS2Buffer(Buffer, Length);
    else if(Sensor==2) ReadSENS3Buffer(Buffer, Length);
    else if(Sensor==3) ReadSENS4Buffer(Buffer, Length);
    else if(Sensor==4) ReadSENS5Buffer(Buffer, Length);
    else if(Sensor==5) ReadSENS6Buffer(Buffer, Length);
    else if(Sensor==6) ReadSENSFRONTBuffer(Buffer, Length);
    else               ReadSENSCUBEBuffer(Buffer, Length);

    if(Clear) {
        if(Sensor==0)      ClearSENS1Buffer();
        else if(Sensor==1) ClearSENS2Buffer();
        else if(Sensor==2) ClearSENS3Buffer();
        else if(Sensor==3) ClearSENS4Buffer();
        else if(Sensor==4) ClearSENS5Buffer();
        else if(Sensor==5) ClearSENS6Buffer();
        else if(Sensor==6) ClearSENSFRONTBuffer();
        else               ClearSENSCUBEBuffer();        
    }
    
    //Return data to PI
    Write_SPI(Buffer, Length);
    Write_SPI(&DONE, 1);
}

void SPI_COMP() {
    //Get data
    unsigned int direction = ReadCOMPASS();

    //Return data to PI
    Write_SPI(&direction, 1);
    Write_SPI(&DONE, 1);
}

void SPI_ECDR(uint8_t Mode, unsigned int Reset) {
    //Get data
    int integral = 0;
    if(Mode==1) {
        if(Reset) integral = enc1_resetAndStore();
        else      integral = enc1_readValue();
    }
    else {
        if(Reset) integral = enc2_resetAndStore();
        else      integral = enc2_readValue();
    }

    //Return data to PI & write DONE to end transaction
    Write_SPI(&integral, 1);
    Write_SPI(&DONE, 1);
}

void SPI_MOTOR(uint8_t Mode, unsigned int Speed, unsigned int direction) {
    if(Mode<=1) {               //If mode is writing
        //send via spi
        if(Mode==0) {
            if(direction > 0) L_motor_constSpeed(FWD, Speed);
            else              L_motor_constSpeed(REV, Speed);
        } else if(Mode==1) {
            if(direction > 0) R_motor_constSpeed(FWD, Speed);
            else              R_motor_constSpeed(REV, Speed);
        }
    } else {                    //if mode is reading
        int motor_speed = 0;
        if(Mode==2) motor_speed = L_motor_SpeedGet();
        else        motor_speed = R_motor_SpeedGet();
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

void SPI_LED(unsigned int Mode, unsigned int period) {
    //Depending on which signal the PI has sent, turn R, G or B on, or turn everything off
    if(Mode==0)     led_const_red_on();
    else if(Mode==1)led_const_grn_on();
    else if(Mode==2)led_const_blue_on();
    else if(Mode==3)led_flash_red_on(period);
    else if(Mode==4)led_flash_grn_on(period);
    else if(Mode==5)led_flash_blue_on(period);
    else            led_TMR5_off_all();
    
    //Write done to spi to finish transaction
    Write_SPI(&DONE,1);
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
    SPI2STATbits.SISEL1 = 1;
    SPI2STATbits.SISEL2 = 0;
   
    /*//Install interrupt to IVT (not required since using correct interrupt name
    int* IVT_LOC = 0x000056;
    *(IVT_LOC) = &SPI_Interrupt;
    */
    //Setup SPI2CON1 for slave mode
    SPI2CON1bits.DISSDO = 0;  //Data out is controlled by module
    SPI2CON1bits.MODE16 = 1;  //16-bit data transfer
    SPI2CON1bits.CKE = 0;     //clocks data on idle to high 
    SPI2CON1bits.SSEN = 0;    //Slave select not used by modeul
    SPI2CON1bits.CKP  = 0;    //Clock is high when clock is high!
    SPI2CON1bits.MSTEN = 0;   //Slave mode
    
    //Setup SPI2CON2 for slave mode
    SPI2CON2bits.FRMEN = 0;   //Disable frame support
    SPI2CON2bits.SPIFSD = 1;  //Frame sync pulse set for slave (possibly unnecesary)
    
    SPI2CON1bits.SMP = 0;     //Slave mode
    SPI2STATbits.SPIROV = 0;  //Clear SPIROV bit
    SPI2CON2bits.SPIBEN = 0;  //Enable 16-byte buffer
    SPI2STATbits.SPIEN = 1;   //Enable SPI operation
}

//SPI Interrupt code
void __attribute__((__interrupt__, auto_psv)) _SPI2Interrupt(void) {   
    //When interrupt triggers, data has been received in Buffer.
    //First data in buffer is always command word!
    spi_info.command = (unsigned int) SPI2BUF;
    //Remaining data goes in "info" buffer
    for(int i=0;i<3;i++) spi_info.info[i] = (unsigned int) SPI2BUF;
  
    //Ensure the receive buffer is empty;
    while(!SPI2STATbits.SRXMPT) unsigned int empty = SPI2BUF;
    
    //Clear interrupt flag
    IFS2bits.SPI2IF = 0;
}

//Discrete SPI function handler
void SPI_Function() {
    //Check if command is a state change or a function call
    if (spi_info.command >= 0x0080) {
        Next_State = (state_t) spi_info.command;    //if a state, change next state to it   
        
        //Set stop conditions
        if(spi_info.info[0]==0)     state_conditions.stop = TIME;
        else if(spi_info.info[0]==1)state_conditions.stop = DISTANCE;
        else                        state_conditions.stop = NONE;
        
        //set stop condition value
        state_conditions.value = spi_info.info[1];
        
        Write_SPI(&DONE, 1);                        //Send "DONE" to PI   
    } else {
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
            case WRITE_MOTOR_LEFT: {
                SPI_MOTOR(0, spi_info.info[0], spi_info.info[1]);
                break;}
            case WRITE_MOTOR_RIGHT: {
                SPI_MOTOR(1, spi_info.info[0], spi_info.info[1]);
                break;}
            case READ_MOTOR_LEFT: {
                SPI_MOTOR(2);
                break;}
            case READ_MOTOR_RIGHT: {
                SPI_MOTOR(3);
                break;}
            case READ_ECDR1: {
                SPI_ECDR(1, spi_info.info[0]);
                break;}
            case READ_ECDR2: {
                SPI_ECDR(2, spi_info.info[0]);
                break;}
            case READ_ECDR1_SUM: {
                SPI_ECDR(1, spi_info.info[0]);
                break;}
            case READ_ECDR2_SUM: {
                SPI_ECDR(2, spi_info.info[0]);
                break;}
            case READ_COMP: {
                SPI_COMP();
                break;}
            case READ_PSNS1: {
                SPI_PSNS(0,spi_info.info[0],spi_info.info[1]);
                break;}
            case READ_PSNS2: {
                SPI_PSNS(1,spi_info.info[0],spi_info.info[1]);
                break;}
            case READ_PSNS3: {
                SPI_PSNS(2,spi_info.info[0],spi_info.info[1]);
                break;}
            case READ_PSNS4: {
                SPI_PSNS(3,spi_info.info[0],spi_info.info[1]);
                break;}
            case READ_PSNS5: {
                SPI_PSNS(4,spi_info.info[0],spi_info.info[1]);
                break;}
            case READ_PSNS6: {
                SPI_PSNS(5,spi_info.info[0],spi_info.info[1]);
                break;}
            case READ_PSNSFNT: {
                SPI_PSNS(6,spi_info.info[0],spi_info.info[1]);
                break;}
            case READ_PSNSCBE: {
                SPI_PSNS(7,spi_info.info[0],spi_info.info[1]);
                break;}
            case WRITE_LED: {
                SPI_LED(spi_info.info[0], spi_info.info[1]);
                break;}
            default:    //do nothing in default case
        }        
    }
       
    //clear spi_info structure
    spi_info.command = 0;
    for(int i=0;i<3;i++) spi_info.info[i] = 0;
}
