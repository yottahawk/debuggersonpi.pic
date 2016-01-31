/**
  OC2 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    oc2.h

  @Summary
    This is the generated header file for the OC2 driver using MPLAB(c) Code Configurator

  @Description
    This header file provides APIs for driver for OC2.
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

#ifndef _OC2_H
#define _OC2_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: Data Types
*/

/** OC2 Fault Number

  @Summary
    Defines the fault number

  @Description
    This type defines the various faults supported.

  Remarks:
    None
*/

typedef enum
{   
    /* Fault 0 */
    OC2_FAULT0        /*DOM-IGNORE-BEGIN*/  = 0,/*DOM-IGNORE-END*/
} OC2_FAULTS;

/**
Deprecated Fault enumeration
*/
typedef enum
{
    /* Fault 0 */
    DRV_OC2_FAULT0        /*DOM-IGNORE-BEGIN*/  = 0,/*DOM-IGNORE-END*/
} DRV_OC2_FAULTS;

/**
  Section: Interface Routines
*/


/**
  @Summary
    This function initializes OC instance : 2

  @Description
    This routine initializes the OC2 driver instance for : 2
    index, making it ready for clients to open and use it.
    This routine must be called before any other OC2 routine is called.
	
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    uint16_t priVal,secVal;
    bool completeCycle = false;
    priVal = 0x1000;
    secVal = 0x2000;
    OC2_FAULTS faultNum = OC2_FAULT0;

    OC2_Initialize();
    
    OC2_CentreAlignedPWMConfig( priVal, secVal );
  
    OC2_Start();

    while(1)
    {
        faultStat =  OC2_FaultStatusGet( faultNum );

        if(faultStat)
        {
            OC2_FaultStatusClear( faultNum );
        }

        completeCycle = OC2_IsCompareCycleComplete( void );
        if(completeCycle)
        {
            OC2_Stop();
        }
    }
    </code>

*/

void OC2_Initialize (void);
/**
    void DRV_OC2_Initialize(void)
*/
void DRV_OC2_Initialize(void) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC2_Initialize instead. ")));

/**
  @Summary
    Maintains the driver's state machine and implements its ISR

  @Description
    This routine is used to maintain the driver's internal state
    machine and implement its ISR for interrupt-driven implementations.
  
  @Preconditions
    None.

  @Param
    None.

  @Returns
    None.

  @Example
    <code>
    while (true)
    {
        OC2_Tasks();

        // Do other tasks
    }
    </code>
    
*/
void OC2_Tasks( void );

/**
    void DRV_OC2_Tasks(void)
*/
void DRV_OC2_Tasks(void) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC2_Tasks instead. ")));


/**
  @Summary
    Enables the OC module with the corresponding operation mode.

  @Description
    This routine enables the OC module with the corresponding operation mode.

  @Preconditions
    OC2_Initialize function should have been called 

  @Param
    None.

  @Returns
    None.

  @Example 
    Refer to OC2_Initialize() for an example	
 
*/
void OC2_Start( void );

/**
    void DRV_OC2_Start(void)
*/
void DRV_OC2_Start(void) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC2_Start instead. ")));

/**
  @Summary
    Disables the OC module.

  @Description
    This routine disables the OC module.

  @Preconditions
    OC2_Initialize function should have been called 

  @Param
    None.

  @Returns
    None.

*/
void OC2_Stop( void );

/**
    void DRV_OC2_Stop(void)
*/
void DRV_OC2_Stop(void) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC2_Stop instead. ")));

/**
  @Summary
    Sets the primary compare value.

  @Description
    This routine sets the primary compare value.

  @Preconditions
    OC2_Initialize function should have been called 

  @Param
    None.

  @Returns
    None.

  @Example 
    <code>
        uint16_t value = 0x1000;
        OC2_SingleCompareValueSet( value );
    <code>
*/

void OC2_SingleCompareValueSet( uint16_t value );

/**
    void DRV_OC2_SingleCompareValueSet(uint16_t value)
*/
void DRV_OC2_SingleCompareValueSet(uint16_t value) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC2_SingleCompareValueSet instead. ")));

/**
  @Summary
    Sets the primary and secondary compare value.

  @Description
    This routine sets the primary and secondary compare value.

  @Preconditions
    OC2_Initialize function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        uint16_t secVal = 0x2000;
        OC2_DualCompareValueSet( priVal,secVal );
    <code>
  	
*/

void OC2_DualCompareValueSet( uint16_t priVal, uint16_t secVal );

/**
    void DRV_OC2_DualCompareValueSet(uint16_t priVal, uint16_t secVal)
*/
void DRV_OC2_DualCompareValueSet(uint16_t priVal, uint16_t secVal) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC2_DualCompareValueSet instead. ")));

/**
  @Summary
    Sets the primary and secondary compare value for Center Aligned PWM

  @Description
    This routine sets the primary and secondary compare value for Center Aligned PWM.

  @Preconditions
    OC2_Initialize function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	
	
  @Returns
    None.

  @Example 
    Refer to OC2_Initialize() for an example

*/
void OC2_CentreAlignedPWMConfig( uint16_t priVal, uint16_t secVal );

/**
    void DRV_OC2_CentreAlignedPWMConfig(uint16_t priVal, uint16_t secVal)
*/
void DRV_OC2_CentreAlignedPWMConfig(uint16_t priVal, uint16_t secVal) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC2_CentreAlignedPWMConfig instead. ")));

/**
  @Summary
    Sets the primary and secondary compare value for Edge Aligned PWM.

  @Description
    This routine sets the primary and secondary compare value for Edge Aligned PWM.

  @Preconditions
    OC2_Initialize function should have been called 

  @Param
    priVal - 16 bit primary compare value.
    secVal - 16 bit primary compare value.	

  @Returns
    None.

  @Example 
    <code>
        uint16_t priVal = 0x1000;
        uint16_t secVal = 0x2000;
        OC2_EdgeAlignedPWMConfig( priVal,secVal );
    <code> 
 	
*/
void OC2_EdgeAlignedPWMConfig( uint16_t priVal, uint16_t secVal );

/**
    void DRV_OC2_EdgeAlignedPWMConfig(uint16_t priVal, uint16_t secVal)
*/
void DRV_OC2_EdgeAlignedPWMConfig(uint16_t priVal, uint16_t secVal) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC2_EdgeAlignedPWMConfig instead. ")));

/**
  @Summary
    Gets the status of the compare cycle completion.

  @Description
    This routine gets the status of the compare cycle completion.

  @Preconditions
    OC2_Initialize function should have been called 

  @Param
    None.

  @Returns
    Boolean value describing the current status of the cycle completion. Returns
    true  : When the compare cycle has completed. 
    false : When the compare cycle has not completed. 

  @Example 
    Refer to OC2_Initialize() for an example
	

*/
bool OC2_IsCompareCycleComplete( void );

/**
    bool DRV_OC2_IsCompareCycleComplete(void)
*/
bool DRV_OC2_IsCompareCycleComplete(void) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC2_IsCompareCycleComplete instead. ")));

/**
  @Summary
    Gets the status of the PWM fault condition occurrence.

  @Description
    This routine gets the status of the PWM fault condition occurrence.
  
  @Preconditions
    OC2_Initialize function should have been called 

  @Param
    faultNum - The fault number

  @Returns
    boolean value describing the occurrence of the fault condition.
    true  : When the specified fault has occurred.
    false : When the specified fault has not occurred.
	
  @Example 
    Refer to OC2_Initialize() for an example 
 

*/
bool OC2_FaultStatusGet( OC2_FAULTS faultNum );

/**
    bool DRV_OC2_FaultStatusGet(DRV_OC2_FAULTS faultNum)
*/
bool DRV_OC2_FaultStatusGet(DRV_OC2_FAULTS faultNum) __attribute__((deprecated ("\nThis will be removed in future MCC releases. \nUse OC2_FaultStatusGet instead. ")));


#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_OC2_H
    
/**
 End of File
*/
