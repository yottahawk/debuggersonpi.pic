
/**
  OC2 Generated Driver API Source File

  @Company
    Microchip Technology Inc.

  @File Name
    oc2.c

  @Summary
    This is the generated source file for the OC2 driver using MPLAB(c) Code Configurator

  @Description
    This source file provides APIs for driver for OC2.
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
#include "oc2.h"

/** OC Mode.

  @Summary
    Defines the OC Mode.

  @Description
    This data type defines the OC Mode of operation.

*/

static uint16_t         gOC2Mode;

/**
  Section: Driver Interface
*/


void OC2_Initialize (void)
{
    // OC2RS 64; 
    OC2RS = 0x0040;
    // OC2R 1; 
    OC2R = 0x0001;
    // OCSIDL disabled; OCM PWM mode on OC, Fault pin is disabled; OCTSEL TMR3; 
    OC2CON = 0x000E;
	
    gOC2Mode = OC2CONbits.OCM;
}

/**
    void DRV_OC2_Initialize (void)
*/
void DRV_OC2_Initialize (void)
{
    OC2_Initialize ();
}


void OC2_Tasks( void )
{
    if(IFS0bits.OC2IF)
    {
        IFS0bits.OC2IF = 0;
    }
}

/**
    void DRV_OC2_Tasks (void)
*/
void DRV_OC2_Tasks (void)
{
    OC2_Tasks ();
}

void OC2_Start( void )
{
    OC2CONbits.OCM = gOC2Mode;
}

/**
    void DRV_OC2_Start (void)
*/
void DRV_OC2_Start (void)
{
    OC2_Start ();
}

void OC2_Stop( void )
{
    OC2CONbits.OCM = 0;
}

/**
    void DRV_OC2_Stop (void)
*/
void DRV_OC2_Stop (void)
{
    OC2_Stop ();
}

void OC2_SingleCompareValueSet( uint16_t value )
{
    OC2R = value;
}

/**
    void DRV_OC2_SingleCompareValueSet (uint16_t value)
*/
void DRV_OC2_SingleCompareValueSet (uint16_t value)
{
    OC2_SingleCompareValueSet (value);
}

void OC2_DualCompareValueSet( uint16_t priVal, uint16_t secVal )
{
    OC2R = priVal;
	
    OC2RS = secVal;
}

/**
    void DRV_OC2_DualCompareValueSet (uint16_t priVal, uint16_t secVal)
*/
void DRV_OC2_DualCompareValueSet (uint16_t priVal, uint16_t secVal)
{
    OC2_DualCompareValueSet ( priVal, secVal);
}

void OC2_CentreAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{
    OC2R = priVal;
	
    OC2RS = secVal;
}

/**
    void DRV_OC2_CentreAlignedPWMConfig (uint16_t priVal, uint16_t secVal)
*/
void DRV_OC2_CentreAlignedPWMConfig (uint16_t priVal, uint16_t secVal)
{
    OC2_CentreAlignedPWMConfig (priVal, secVal);
}

void OC2_EdgeAlignedPWMConfig( uint16_t priVal, uint16_t secVal )
{
    OC2R = priVal;
	
    OC2RS = secVal;
}

/**
    void DRV_OC2_EdgeAlignedPWMConfig (uint16_t priVal, uint16_t secVal)
*/
void DRV_OC2_EdgeAlignedPWMConfig (uint16_t priVal, uint16_t secVal)
{
    OC2_EdgeAlignedPWMConfig (priVal, secVal);
}

bool OC2_IsCompareCycleComplete( void )
{
    return(IFS0bits.OC2IF);
}

/**
    bool DRV_OC2_IsCompareCycleComplete (void)
*/
bool DRV_OC2_IsCompareCycleComplete (void)
{
    return(OC2_IsCompareCycleComplete ());
}

bool OC2_FaultStatusGet( OC2_FAULTS faultNum )
{
    bool status;
    /* Return the status of the fault condition */
   
    switch(faultNum)
    { 
        case OC2_FAULT0:status = OC2CONbits.OCFLT;
            break;
        default :
            break;

    }
    return(status);
}

/**
    bool DRV_OC2_FaultStatusGet (DRV_OC2_FAULTS faultNum)
*/
bool DRV_OC2_FaultStatusGet (DRV_OC2_FAULTS faultNum)
{
    return(OC2_FaultStatusGet (faultNum));
}


/**
 End of File
*/
