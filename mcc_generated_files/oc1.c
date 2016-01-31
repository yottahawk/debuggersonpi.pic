
/**
  OC1 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    oc1.c

  @Summary
    This is the generated source file for the OC1 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for driver for OC1.
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
#include "oc1.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gOC1Mode;

/**
  Section: Driver Interface
*/


void OC1_Initialize (void)
{
    // OC1RS 64; 
    OC1RS = 0x0040;
    // OC1R 1; 
    OC1R = 0x0001;
    // OCSIDL disabled; OCM PWM mode on OC, Fault pin is disabled; OCTSEL TMR2; 
    OC1CON = 0x0006;
	
    gOC1Mode = OC1CONbits.OCM;
}

/**
    void DRV_OC1_Initialize (void)
*/
void DRV_OC1_Initialize (void)
{
    OC1_Initialize ();
}


void OC1_Tasks( void )
{
    if(IFS0bits.OC1IF)
    {
        IFS0bits.OC1IF = 0;
    }
}

/**
    void DRV_OC1_Tasks (void)
*/
void DRV_OC1_Tasks (void)
{
    OC1_Tasks ();
}

void OC1_Start( void )
{
    OC1CONbits.OCM = gOC1Mode;
}

/**
    void DRV_OC1_Start (void)
*/
void DRV_OC1_Start (void)
{
    OC1_Start ();
}

void OC1_Stop( void )
{
    OC1CONbits.OCM = 0;
}

/**
    void DRV_OC1_Stop (void)
*/
void DRV_OC1_Stop (void)
{
    OC1_Stop ();
}

void OC1_SingleCompareValueSet( uint16_t value )
{
    OC1R = value;
}

/**
    void DRV_OC1_SingleCompareValueSet (uint16_t value)
*/
void DRV_OC1_SingleCompareValueSet (uint16_t value)
{
    OC1_SingleCompareValueSet (value);
}

void OC1_DualCompareValueSet( uint16_t priVal, uint16_t secVal )
{
    OC1R = priVal;
	
    OC1RS = secVal;
}

/**
    void DRV_OC1_DualCompareValueSet (uint16_t priVal, uint16_t secVal)
*/
void DRV_OC1_DualCompareValueSet (uint16_t priVal, uint16_t secVal)
{
    OC1_DualCompareValueSet ( priVal, secVal);
}

void OC1_CentreAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{
    OC1R = priVal;
	
    OC1RS = secVal;
}

/**
    void DRV_OC1_CentreAlignedPWMConfig (uint16_t priVal, uint16_t secVal)
*/
void DRV_OC1_CentreAlignedPWMConfig (uint16_t priVal, uint16_t secVal)
{
    OC1_CentreAlignedPWMConfig (priVal, secVal);
}

void OC1_EdgeAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{
    OC1R = priVal;
	
    OC1RS = secVal;
}

/**
    void DRV_OC1_EdgeAlignedPWMConfig (uint16_t priVal, uint16_t secVal)
*/
void DRV_OC1_EdgeAlignedPWMConfig (uint16_t priVal, uint16_t secVal)
{
    OC1_EdgeAlignedPWMConfig (priVal, secVal);
}

bool OC1_IsCompareCycleComplete( void )
{
    return(IFS0bits.OC1IF);
}

/**
    bool DRV_OC1_IsCompareCycleComplete (void)
*/
bool DRV_OC1_IsCompareCycleComplete (void)
{
    return(OC1_IsCompareCycleComplete ());
}

bool OC1_FaultStatusGet( OC1_FAULTS faultNum )
{
    bool status;
    /* Return the status of the fault condition */
   
    switch(faultNum)
    { 
        case OC1_FAULT0:status = OC1CONbits.OCFLT;
            break;
        default :
            break;

    }
    return(status);
}

/**
    bool DRV_OC1_FaultStatusGet (DRV_OC1_FAULTS faultNum)
*/
bool DRV_OC1_FaultStatusGet (DRV_OC1_FAULTS faultNum)
{
    return(OC1_FaultStatusGet (faultNum));
}


/**
 End of File
*/
