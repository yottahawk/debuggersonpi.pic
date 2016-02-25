#include "spi.h"

#define TIMEOUT 10000

spi_info_t spi_info;

const unsigned int DONE = 0xFFFE;
const unsigned int Data = 0xFFFD;

//Function to write to spi link
void Write_SPI(const unsigned int* buffer, unsigned int length) {
    //For each byte in the buffer...
    for(int i=0;i<length;i++) {
        while(SPI2STATbits.SPITBF) {} //wait until there is space in the buffer
        //invert bytes of int
        unsigned char b1 = (unsigned char) ((buffer[i] >> 8) & 0x00FF);
        unsigned char b2 = (unsigned char) ((buffer[i]) & 0x00FF);
        
        unsigned int i1 = (((unsigned int) b1) & 0x00FF);
        unsigned int i2 = ((((unsigned int) b2) & 0x00FF) << 8);
        //buffer[i] = i2 | i1;  
        i2 = i2 | i1;
        
        SPI2BUF = i2;
    }
    
    //if sending "Done" to PI, wait until "Done" received, then empty buffer. This signals end of transaction.
    if(buffer[0] == DONE) {
        unsigned int n = 0;
        while(n++ < 0xFFFE) {
            unsigned int check = (unsigned int) SPI2BUF;
            if(check == DONE) {
                break;
            }
        }
        
        //Ensure the receive buffer is empty;
        while(!SPI2STATbits.SRXMPT) {unsigned int empty = SPI2BUF;}

        //Reset SPI module (tends to get out of sync)
        SPI2STATbits.SPIEN = 0;
        SPI2STATbits.SPIEN = 1;
    }  
}

void SPI_ROOM() {
    //Read DIP switches
    unsigned int roomdata = (unsigned int) Current_Room;
    
    //Send via SPI
    Write_SPI(&Data, 1);
    Write_SPI(&roomdata, 1);
    Write_SPI(&DONE, 1);    
}

void SPI_PSNS(unsigned char Sensor, unsigned int Length, unsigned int Clear) {
    //Buffer to send data from
    unsigned int* Buffer; 
 
//    //Get data
    if(Sensor==0)      ReadSENSLBuffer(Buffer, Length);
    else if(Sensor==1) ReadSENSRBuffer(Buffer, Length);
//    else if(Sensor==2) ReadSENS3Buffer(Buffer, Length);
//    else if(Sensor==3) ReadSENS4Buffer(Buffer, Length);
//    else if(Sensor==4) ReadSENS5Buffer(Buffer, Length);
//    else if(Sensor==5) ReadSENS6Buffer(Buffer, Length);
    else if(Sensor==6) ReadSENSFBuffer(Buffer, Length);
    else if(Sensor==7) ReadSENSCBuffer(Buffer, Length);
//
    if(Clear) {
        if(Sensor==0)      ClearSENSLBuffer();
        else if(Sensor==1) ClearSENSRBuffer();
//        else if(Sensor==2) ClearSENS3Buffer();
//        else if(Sensor==3) ClearSENS4Buffer();
//        else if(Sensor==4) ClearSENS5Buffer();
//        else if(Sensor==5) ClearSENS6Buffer();
        else if(Sensor==6) ClearSENSFBuffer();
        else if(Sensor==7) ClearSENSCBuffer();        
    }
    
    //Return data to PI
    Write_SPI(&Data, 1);
    Write_SPI(Buffer, Length);
    Write_SPI(&DONE, 1);
}

void SPI_DIP() {
    //Read DIP switches
    unsigned int DIP;
    readDIP(&DIP);
    
    //Send via SPI

    Write_SPI(&Data, 1);
    Write_SPI(&DIP, 1);
    Write_SPI(&DONE, 1);
}

void SPI_COMP() {
    //Get data
    int direction = calculateHeading(); // UNCOMMMENT WHEN FUNCTION CREATED!!

    //Return data to PI
    Write_SPI(&Data, 1);
    Write_SPI((unsigned int *) &direction, 1);
    Write_SPI(&DONE, 1);
}

void SPI_ECDR(unsigned char Mode, unsigned int Reset) {
    //Get data
    int integral = 0;
    if(Mode==1) {
        if(Reset) integral = enc1_resetAndStore();
        else      integral = enc1_Store();
    }
    else {
        if(Reset) integral = enc2_resetAndStore();
        else      integral = enc2_Store();
    }

    //Return data to PI & write DONE to end transaction
    Write_SPI(&Data, 1);
    Write_SPI((const unsigned int*) &integral, 1);
    Write_SPI(&DONE, 1);
}

void SPI_MOTOR(unsigned char Mode, unsigned int Speed, unsigned int direction) {
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
        Write_SPI(&Data, 1);
        Write_SPI((const unsigned int*) &motor_speed, 1);
    }
    
    //Write done to spi to finish transaction
    Write_SPI(&DONE,1);
}

void SPI_GRABBER(unsigned char Mode) {
    //placeholder variable for readgrabber
    unsigned int val=0xFFFF;
    
    //Call appropriate grabber function
    if(Mode==0)     OpenGRABBER();          //Call appropriate function
    else if(Mode==1)CloseGRABBER();
    else      val = ReadGRABBER();
    
    //Write val to SPI if readgrabber has been called
    Write_SPI(&Data, 1);
    if(val != 0xFFFF) Write_SPI(&val,1);
    
    Write_SPI(&DONE, 1);        //Write "DONE" signal to PI   
}

void SPI_LED(unsigned int Mode, unsigned int period) {
    //Depending on which signal the PI has sent, turn R, G or B on, or turn everything off
    if(Mode==0)     led_const_red_on();
    else if(Mode==1)led_const_grn_on();
    else if(Mode==2)led_const_blue_on();
    else if(Mode==3){
        led_init_timer();               // enables tmr5 interrupts for led flashing routines.
        led_flash_red_on(period);}
    else if(Mode==4){
        led_init_timer();               // enables tmr5 interrupts for led flashing routines.
        led_flash_grn_on(period);}
    else if(Mode==5){
        led_init_timer();
        led_flash_blue_on(period);}
    else            led_TMR5_off_all();
    
    //Write done to spi to finish transaction
    Write_SPI(&DONE,1);
}

void Initialise_SPI() {
    //Clear SPI2BUF register
    //SPI2BUF = 0x0000;
    
    //Interrupts
    //Clear Flag
    IFS2bits.SPI2IF = 0; //Clear bit 1
    //Allow enable
    IEC2bits.SPI2IE = 1; //Set bit 1
    //Set priority to 0 
    IPC8bits.SPF2IP0 = 1;
    IPC8bits.SPI2IP1 = 1;
    IPC8bits.SPI2IP2 = 1;
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
    //SPI2CON2bits.SPIFSD = 1;  //Frame sync pulse set for slave (possibly unnecesary)
    
    SPI2CON1bits.SMP = 0;     //Slave mode
    SPI2STATbits.SPIROV = 0;  //Clear SPIROV bit
    SPI2CON2bits.SPIBEN = 1;  //Enable buffer
    SPI2STATbits.SPIEN = 1;   //Enable SPI operation

    //Ensure the receive buffer is empty;
    while(!SPI2STATbits.SRXMPT) {unsigned int empty = SPI2BUF;}
}

//Discrete SPI function handler
void SPI_Function(spi_state_data* state_data) {
    //Check if command is a state change or a function call
    if (spi_info.command >= 0x0080) {
        state_data->state = (state_t) (spi_info.command);    //if a state, change next state to it   
        
        //Set stop conditions
        state_data->state_data.data_type = (condition_t) spi_info.info[0];
        //set stop condition value
        state_data->state_data.value = spi_info.info[1];
    } else {
        //This function is called if the PI wants to call certain functions
        //behaviour depends on the function the PI is calling
        switch ((state_t) spi_info.command) {
            case OPEN_GRABBER: {
                SPI_GRABBER(0);
                break;}
            case CLOSE_GRABBER: {
                SPI_GRABBER(1);
                break;}
            case READ_GRABBER: {
                SPI_GRABBER(2);
                break;}
            case WRITE_MOTOR_LEFT_FWD: {
                SPI_MOTOR(0, spi_info.info[0], 1);
                break;}
            case WRITE_MOTOR_RIGHT_FWD: {
                SPI_MOTOR(1, spi_info.info[0], 1);
                break;}
            case WRITE_MOTOR_LEFT_REV: {
                SPI_MOTOR(0, spi_info.info[0], 0);
                break;}
            case WRITE_MOTOR_RIGHT_REV: {
                SPI_MOTOR(1, spi_info.info[0], 0);
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
            case READ_DIP: {
                SPI_DIP();
                break;}
            case READ_ROOM: {
                SPI_ROOM();
                break;
            }
            case STOPPED: break;
            case OL_FORWARD: break;
            case OL_LEFT: break;
            case OL_RIGHT: break;
            case OL_REVERSE: break;
            case OL_REV_LEFT: break;
            case OL_REV_RIGHT: break;
            case COMP_FORWARD: break;
            case COMP_LEFT: break;
            case COMP_RIGHT: break;
            case COMP_REVERSE: break;
            case COMP_REV_RIGHT: break;
            case COMP_REV_LEFT: break;
            case ECDR_FORWARD: break;
            case ECDR_LEFT: break;
            case ECDR_RIGHT: break;
            case ECDR_REVERSE: break;
            case ECDR_REV_LEFT: break;
            case ECDR_REV_RIGHT: break;
            case PSNS_FORWARD: break;
            case PSNS_LEFT: break;
            case PSNS_RIGHT: break;
            case PSNS_REVERSE: break;
            case PSNS_REV_LEFT: break;
            case PSNS_REV_RIGHT: break;   
            case PSNS_FORWARD_JUNCTION_DETECT: break;
            //default:    //do nothing in default case
        }        
    }
       
    //clear spi_info structure
    spi_info.command = 0;
    for(int i=0;i<7;i++) spi_info.info[i] = 0;
}
