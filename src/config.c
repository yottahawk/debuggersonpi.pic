/*
 * File:   config.c
 * Author: 
 * 
 * This file contains all the configuration to occur before the device 
 * starts processing data. 
 *
 * Created on 31 January 2016, 18:28
 */

#include <xc.h>

// Configuration bits to initialise oscillator etc.
// CONFIG2
#pragma config POSCMOD = XT       // Primary Oscillator Select->XT Oscillator mode selected
#pragma config OSCIOFNC = OFF     // Primary Oscillator Output Function->OSC2/CLKO/RC15 functions as CLKO (FOSC/2)
#pragma config FCKSM = CSDCMD     // Clock Switching and Monitor->Clock switching and Fail-Safe Clock Monitor are disabled
#pragma config FNOSC = PRI        // Oscillator Select->Primary Oscillator (XT, HS, EC)
#pragma config IESO = OFF         // Internal External Switch Over Mode->IESO mode (Two-Speed Start-up) enabled

// CONFIG1
#pragma config WDTPS = PS32768    // Watchdog Timer Postscaler->1:32,768
#pragma config FWPSA = PR128      // WDT Prescaler->Prescaler ratio of 1:128
#pragma config WINDIS = ON        // Watchdog Timer Window->Standard Watchdog Timer enabled,(Windowed-mode is disabled)
#pragma config FWDTEN = OFF       // Watchdog Timer Enable->Watchdog Timer is disabled
#pragma config ICS = PGx2         // Comm Channel Select->Emulator/debugger uses EMUC2/EMUD2
#pragma config COE = OFF          // Set Clip On Emulation Mode->Reset Into Operational Mode
#pragma config BKBUG = OFF        // Background Debug->Device resets into Operational mode
#pragma config GWRP = OFF         // General Code Segment Write Protect->Writes to program memory are allowed
#pragma config GCP = OFF          // General Code Segment Code Protect->Code protection is disabled
#pragma config JTAGEN = OFF       // JTAG Port Enable->JTAG port is disabled

void initialise_pinmap(void)
{
    ///////////////////////MODS/////////////////////////////////////////////////
    /*
     * Any mods made where the actual circuit differs to the schematic are
     * documented here.
     * 
     * V_BATT_SENSE_ADC (31) -> RB15 (30)
     * PI_CS (54)            -> RG9 (8)
     * GRAB_MTR_4 (30)       -> RE0 (60)
     * WHEEL_ENC_1 (11)      -> RD8 (42)
     * WHEEL_ENC_2           -> RD9 (43)
     *
     */
    ///////////////////////TRISx////////////////////////////////////////////////
    // Data direction register (Input=1/Output=0)
    // All pins are inputs by default after reset
    enum IO{OUT=0,IN=1};
    
    // TRISA
    // Port A is not present on this device.
    
    // TRISB
    TRISBbits.TRISB0  = IN;  // VREF+           (16)
    TRISBbits.TRISB1  = IN;  // VREF-           (15)
    TRISBbits.TRISB2  = IN;  // SENS_FRONT      (14)
    TRISBbits.TRISB3  = IN;  // SENS_R          (13)
    TRISBbits.TRISB4  = IN;  // PUSH_SW         (12)
    // TRISBbits.TRISB5  = IN;  // WHEEL_ENC_1     (11) //Bodged onto pin 42
    TRISBbits.TRISB6  = IN;  // PGC             (17)
    TRISBbits.TRISB7  = IN;  // PGD             (18)
    TRISBbits.TRISB8  = IN;  // LINE_R_F        (21)
    TRISBbits.TRISB9  = IN;  // LINE_R_B        (22)
    TRISBbits.TRISB10 = IN;  // LINE_L_B        (23)
    TRISBbits.TRISB11 = IN;  // LINE_L_F        (24)
    TRISBbits.TRISB12 = IN;  // SENSE_CUBE      (27)
    TRISBbits.TRISB13 = IN;  // SENS_L          (28)
    TRISBbits.TRISB14 = OUT; // PS_MOTOR_EN     (29)
    TRISBbits.TRISB15 = IN;  // V_BATT_SENSE_AC (30)
    
    // TRISC
    TRISCbits.TRISC12 = IN;  // OSC1            (39)
    TRISCbits.TRISC13 = IN;  // OSC2            (40)
    TRISCbits.TRISC14 = OUT; // GYRO_DEN_G      (47)
    TRISCbits.TRISC15 = OUT; // ACC_CS_A        (48)
    
    // TRISD
    TRISDbits.TRISD0  = OUT; // GYRO_CS_G       (46)
    TRISDbits.TRISD1  = OUT; // M1_FWD          (49)
    TRISDbits.TRISD2  = OUT; // M1_REV          (50)
    TRISDbits.TRISD3  = OUT; // M2_FWD          (51)
    TRISDbits.TRISD4  = OUT; // M2_REV          (52)
    TRISDbits.TRISD5  = IN;  // MAG/COMP_DRDY   (53)
    TRISDbits.TRISD7  = OUT; // PI_SIG          (55)
    //TRISDbits.TRISD8  = IN;  // ACC_INT2A       (42) //Traces cut
    TRISDbits.TRISD8  = IN;  // WHEEL_ENC_1     (42) //Bodge
    //TRISDbits.TRISD9  = IN;  // ACC_INT1A       (43) //Traces cut
    TRISDbits.TRISD9  = IN;  // WHEEL_ENC_2     (43) //Bodge
    TRISDbits.TRISD10 = IN;  // GYRO_INT1G      (44)
    TRISDbits.TRISD11 = IN;  // GYRO_DRDY_G     (45)
    
    // TRISE
    TRISEbits.TRISE0  = OUT; // GRAB_MTR_4      (60)
    TRISEbits.TRISE1  = IN;  // DIP_SW1         (61)
    TRISEbits.TRISE2  = IN;  // DIP_SW2         (62)
    TRISEbits.TRISE3  = IN;  // DIP_SW3         (63)
    TRISEbits.TRISE4  = IN;  // DIP_SW4         (64)
    TRISEbits.TRISE5  = OUT; // BLUE_LED        (1)
    TRISEbits.TRISE6  = OUT; // GRN_LED         (2)
    TRISEbits.TRISE7  = OUT; // RED_LED         (3)
    
    // TRISF
    TRISFbits.TRISF2  = OUT; // GRAB_MTR_2      (34)
    TRISFbits.TRISF3  = OUT; // GRAB_MTR_3      (33)
    TRISFbits.TRISF4  = IN;  // V_BATT_SENSE_ADC    (34)
    // TRISFbits.TRISF5  = IN;  // WHEEL_ENC_2     (32) // Bodged onto pin 43
    TRISFbits.TRISF6  = OUT; // GRAB_MTR_1      (35)
    
    // TRISG
    // This port contains the SPI and I2C pins, which are automatically set as
    // serial port objects when the modules are enabled.
    
    ////////////////////////////////////LATx////////////////////////////////////
    // Writes to LAT register to set output values at startup.
    
    // LATB
    LATBbits.LATB14 = 0;     // PS_MOTOR_EN - disabled (pulled low) by default
    LATBbits.LATB15 = 0;     // GRAB_MTR_4
    
    // LATC
    LATCbits.LATC14 = 0;     // GYRO_DEN_G
    LATCbits.LATC15 = 0;     // ACC_CS_A
    
    //LATD
    LATDbits.LATD0 = 0;      // GYRO_CS_G
    LATDbits.LATD1 = 0;      // M1_FWD
    LATDbits.LATD2 = 0;      // M1_REV
    LATDbits.LATD3 = 0;      // M2_FWD
    LATDbits.LATD4 = 0;      // M2_REV
    LATDbits.LATD7 = 1;      // PI_SIG - active low signal
    
    //LATE
    LATEbits.LATE5 = 1;      // BLUE_LED - off
    LATEbits.LATE6 = 1;      // GRN_LED - off
    LATEbits.LATE7 = 1;      // RED_LED - off
    
    //LATF
    LATFbits.LATF2 = 0;      // GRAB_MTR_2
    LATFbits.LATF3 = 0;      // GRAB_MTR_3
    LATFbits.LATF6 = 0;      // GRAB_MTR_1
 
    ////////////////////////////////ODCx////////////////////////////////////////
    // Set open drain output.
    
    ODCEbits.ODE5  = 1;      // BLUE_LED
    ODCEbits.ODE6  = 1;      // GRN_LED
    ODCEbits.ODE7  = 1;      // RED_LED
    
    ////////////////////////////////AD1PCFG/////////////////////////////////////
    // Set up ADC inputs within the ADC Port Configuration Register    
    // All bits 0 on reset.
    
    AD1PCFG = 0xFFFF; // Set all bits to digital mode by default.
    
    AD1PCFGbits.PCFG2  = 0;  // SENS_FRONT
    AD1PCFGbits.PCFG15 = 0;  // V_BATT_SENSE_ADC
    AD1PCFGbits.PCFG8  = 0;  // LINE_R_F
    AD1PCFGbits.PCFG9  = 0;  // LINE_R_B
    AD1PCFGbits.PCFG10 = 0;  // LINE_L_B
    AD1PCFGbits.PCFG11 = 0;  // LINE_L_F  
}
