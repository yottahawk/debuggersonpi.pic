
/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated header file for the ADC1 driver using MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for ADC1.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC24FJ64GA006
        Driver Version    :  0.5
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB 	          :  MPLAB X 3.20
*/

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

/**
  Section: Included Files
*/

#include <xc.h>
#include "adc1.h"

/**
  Section: Data Type Definitions
*/

/* ADC Driver Hardware Instance Object

  @Summary
    Defines the object required for the maintenance of the hardware instance.

  @Description
    This defines the object required for the maintenance of the hardware
    instance. This object exists once per hardware instance of the peripheral.

 */
typedef struct
{
	uint8_t intSample;
}

ADC_OBJECT;

static ADC_OBJECT adc1_obj;

/**
  Section: Driver Interface
*/


void ADC1_Initialize (void)
{
    // ASAM disabled; ADSIDL disabled; DONE disabled; FORM Absolute decimal result, unsigned, right-justified; SAMP disabled; SSRC Internal counter ends sampling and starts conversion; ADON enabled; 

   AD1CON1 = 0x80E0;

    // CSCNA enabled; VCFG0 VREF+; VCFG1 VREF-; ALTS disabled; BUFM disabled; SMPI 1; 

   AD1CON2 = 0x6400;

    // SAMC 12; ADRC FOSC/2; ADCS 1; 

   AD1CON3 = 0x0C01;

    // CH0SA AN0; CH0SB AN0; CH0NB AVSS; CH0NA AVSS; 

   AD1CHS = 0x0000;

    // CSSL9 enabled; CSSL8 enabled; CSSL7 disabled; CSSL6 disabled; CSSL5 disabled; CSSL4 disabled; CSSL3 disabled; CSSL2 disabled; CSSL15 disabled; CSSL1 disabled; CSSL14 disabled; CSSL0 disabled; CSSL13 disabled; CSSL12 disabled; CSSL11 enabled; CSSL10 enabled; 

   AD1CSSL = 0x0F00;


   adc1_obj.intSample = AD1CON2bits.SMPI;
   
   // Enabling ADC1 interrupt.
   IEC0bits.AD1IE = 1;
}
/**
    void DRV_ADC1_Initialize (void)
*/
void DRV_ADC1_Initialize (void)
{
    ADC1_Initialize ();
}

void ADC1_Start(void)
{
   AD1CON1bits.SAMP = 1;
}
/**
    void DRV_ADC1_Start (void)
*/
void DRV_ADC1_Start (void)
{
    ADC1_Start ();
}
void ADC1_Stop(void)
{
   AD1CON1bits.SAMP = 0;
}
/**
    void DRV_ADC1_Stop (void)
*/
void DRV_ADC1_Stop (void)
{
   ADC1_Stop ();
}
uint16_t ADC1_ConversionResultBufferGet(uint16_t *buffer)
{
    int count;
    uint16_t *ADC16Ptr;

    ADC16Ptr = (uint16_t *)&(ADC1BUF0);

    for(count=0;count<adc1_obj.intSample;count++)
    {
        buffer[count] = (uint16_t)*ADC16Ptr;
        ADC16Ptr++;
    }
    return count;
}
/**
    uint16_t DRV_ADC1_ConversionBufferGet (uint16_t *buffer)
*/
uint16_t DRV_ADC1_ConversionBufferGet (uint16_t *buffer)
{
    return ADC1_ConversionResultBufferGet (buffer);
}
uint16_t ADC1_ConversionResultGet(void)
{
    return ADC1BUF0;
}
/**
    uint16_t DRV_ADC1_ConversionGet (void)
*/
uint16_t DRV_ADC1_ConversionGet (void)
{
    return ADC1_ConversionResultGet ();
}
bool ADC1_IsConversionComplete( void )
{
    return AD1CON1bits.DONE; //Wait for conversion to complete   
}
/**
    bool DRV_ADC1_IsConversionComplete (void)
*/
bool DRV_ADC1_IsConversionComplete (void)
{
    return ADC1_IsConversionComplete ();
}
void ADC1_ChannelSelect( ADC1_CHANNEL channel )
{
    AD1CHS = channel;
}
/**
    void DRV_ADC1_ChannelSelect (DRV_ADC1_CHANNEL channel )
*/
void DRV_ADC1_ChannelSelect (DRV_ADC1_CHANNEL channel )
{
    ADC1_ChannelSelect (channel);
}

void __attribute__ ( ( __interrupt__ , auto_psv ) ) _ADC1Interrupt ( void )
{
    // clear the ADC interrupt flag
    IFS0bits.AD1IF = false;
}


/**
  End of File
*/
