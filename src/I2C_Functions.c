/* (c) 2013 Renishaw plc. All rights reserved.
**
** This source file is the confidential property and copyright of
** Renishaw plc.
** Reproduction or transmission in whole or in part, in any form or
** by any means, electronic, mechanical or otherwise, is prohibited
** without the prior written consent of the copyright owner.
**
** ********************Included header files************************************
** The directories that are searched for included header files are specified in
** the project properties in MPLABX. Control clicking on an included header file
** indicates where it is being taken from.
** *****************************************************************************
**
** ********************Amendments history***************************************
** This dates from when the project resided in the PVCS version control system
** and is no longer relevant.
** *****************************************************************************
** 12/11/2012 - cp137352
**
** Initial Revision Code.
** *****************************************************************************
** 12/12/2012 - cp137352
**
** Fixed indexing bug in functions "fnI2C_CoPro_ReadBytes" &
**  "fnI2C_SecMem_ReadBytes".
** Added new function "fnI2C_CoPro_CheckAck".
** Added new function "fnI2C_SecMem_CheckAck".
** Added new function "fnI2C_SecMem_SendNoAck".
** *****************************************************************************
*/

/*
** This file contains low level I2C functions
** The context of this file has been split up into 3 sections:
** I2C1, I2C2 and I2C3
** The I2C1 peripheral is directly connected to the Co-Processor
** The I2C2 peripheral is directly connected to the secure memory ICs
** The I2C3 peripheral is directly connected to the LED 7 segment display driver
**
*/

/* Microchip Include Files */
#include <p24FJ128GB106.h>
#include <i2c.h>

/* Renishaw Include Files*/
#include "PRIMO Interface.X/I2C_Functions.h"
#include "PRIMO Interface.X/LED_Seg_Handler.h"
#include "PRIMO Interface.X/Hardware_Failure_Mode.h"

/* Register definitions */
#define COPRO_ENABLE I2C1CONbits.SEN
#define COPRO_IDLE I2C1CONbits.PEN
#define COPRO_TX_STATUS I2C1STATbits.TRSTAT
#define COPRO_RESTART_ENABLE I2C1CONbits.RSEN
#define COPRO_ACK_ENABLE I2C1CONbits.ACKEN
#define COPRO_ACK_STATUS I2C1STATbits.ACKSTAT
#define COPRO_WR_COL I2C1STATbits.IWCOL
#define COPRO_I2C_EN I2C1CONbits.I2CEN
#define SECMEM_ENABLE I2C2CONbits.SEN
#define SECMEM_IDLE I2C2CONbits.PEN
#define SECMEM_TX_STATUS I2C2STATbits.TRSTAT
#define SECMEM_RESTART_ENABLE I2C2CONbits.RSEN
#define SECMEM_ACK_ENABLE I2C2CONbits.ACKEN
#define SECMEM_ACK_STATUS I2C2STATbits.ACKSTAT
#define SECMEM_SEND_ACK I2C2CONbits.ACKDT
#define SECMEM_WR_COL I2C2STATbits.IWCOL
#define SECMEM_I2C_EN I2C2CONbits.I2CEN
#define SEGDISP_ENABLE I2C3CONbits.SEN
#define SEGDISP_IDLE I2C3CONbits.PEN
#define SEGDISP_TX_STATUS I2C3STATbits.TRSTAT
#define SEGDISP_ACK_STATUS I2C3STATbits.ACKSTAT
#define SEGDISP_WR_COL I2C3STATbits.IWCOL
#define SEGDISP_I2C_EN I2C3CONbits.I2CEN

static const UINT16 I2CEN   = 0x8000; /* Enable I2C module */
static const UINT16 DISSLW  = 0x0200; /* Slew rate control disabled */
static const UINT16 ACKDT   = 0x0020; /* Send NACK during acknowledge */

/* I2C baud rates for a system clock @ 32MHz */
static const UINT16 I2C_BAUD_400K = 0x0027; /* I2C baud rate 400KHz Setting */
static const UINT16 I2C_BAUD_1M   = 0x000F; /* I2C baud rate 1MHz Setting */
/* number of times to retry if a write collision is detected */
static const UINT8 RETRY_COUNT          = 3;
/* "MasterWriteI2C1" returns -1 if a write collision occurs */
static const INT8 I2C_WRITE_COLLISION   = -1;
/* ACKSTAT register bit = 1 for NACK detected last */
static const UINT8 NoAck                = 1;


/* Local Prototypes */
static void fnI2C_SegDisp_StartI2C( void );
static void fnI2C_SegDisp_StopI2C( void );

/*************************************************************************
**    This section provides functions for interfacing the Co-Processor
**    to the PIC via the I2C1 PIC peripheral
**
**************************************************************************/

/*----------------------------------------------------------------------------
** Function: fnI2C_CoPro_OpenI2C()
**
** This function configures and opens I2C1
**
** Inputs:  None
**
** Returns:  None
*/
void fnI2C_CoPro_OpenI2C( void )
{
   /* Setup the I2C config register and enable the port */
   OpenI2C1( I2CEN | DISSLW | ACKDT, I2C_BAUD_400K );
   /* wait for the port to go idle */
   IdleI2C1();
}

/*----------------------------------------------------------------------------
** Function: fnI2C_CoPro_CloseI2C()
**
** This function closes the I2C1 peripheral
**
** Inputs:  None
**
** Returns:  None
*/
void fnI2C_CoPro_CloseI2C( void )
{
   /* wait for the port to go idle */
   IdleI2C1();
   CloseI2C1();
}

/*----------------------------------------------------------------------------
** Function: fnI2C_CoPro_StartI2C()
**
** This function starts the Co-Processor I2C communications
**
** Inputs:  None
**
** Returns:  None
*/
void fnI2C_CoPro_StartI2C( void )
{
   StartI2C1();
   while( COPRO_ENABLE != CLEAR )
   {
      /*do nothing*/
   }
}

/*----------------------------------------------------------------------------
** Function: fnI2C_CoPro_StopI2C()
**
** This function stops the Co-Processor I2C communications and
** changes the I2C peripheral state to idle
**
** Inputs:  None
**
** Returns:  None
*/
void fnI2C_CoPro_StopI2C( void )
{
   StopI2C1();
   while( COPRO_IDLE != CLEAR )
   {
      /*do nothing*/
   }
   /* wait for the port to go idle */
   IdleI2C1();
}

/*----------------------------------------------------------------------------
** Function: fnI2C_CoPro_WriteByte()
**
** This function writes a single byte to the Co-Processor
** If a bus collision is detected the function will retry the write up to
** "RETRY_COUNT" number of times.
**
** Inputs:   Data to write to the Co_processor
**
** Returns:  NOne
*/
void fnI2C_CoPro_WriteByte( const UINT8 CoProWriteData )
{
   UINT8 CollisionRetry             = RETRY_COUNT;
   INT8  I2CWriteStatus             = 0;

   /* If an I2C bus collision occurs retry up to "RETRY_COUNT" times */
   do
   {
      if( COPRO_WR_COL == SET )
      {
         COPRO_WR_COL = CLEAR;
         COPRO_I2C_EN = CLEAR;
         COPRO_I2C_EN = SET;
      }

      /* Write the data to the Co-Processor*/
      I2CWriteStatus = MasterWriteI2C1( CoProWriteData );
      while( COPRO_TX_STATUS != CLEAR )
      {
         /*do nothing*/
      }

      CollisionRetry--;

   }while( (CollisionRetry > 0) && (I2CWriteStatus == I2C_WRITE_COLLISION) );

   /* Check to see if an I2C bus collision occurred */
   if( I2CWriteStatus == I2C_WRITE_COLLISION )
   {
      /* Display an error number to show the I2C has failed */
      fnHWF_IndicateError( SEG_DISP_COPRO_WR_BYTE_FLD );
   }
}

/*----------------------------------------------------------------------------
** This function writes several bytes to the coprocessor
**
** Inputs:  Pointer to data to write to the coprocessor
**          Number of bytes to write.
**
** Returns: None
**
*/
void fnI2C_CoPro_WriteBytes( const UINT8 * data,  UINT16 numBytes)
{
   UINT16 i;

   for (i = 0; i < numBytes; i++)
   {
      fnI2C_CoPro_WriteByte( data[i] );
   }
}

/*----------------------------------------------------------------------------
** Function: fnI2C_CoPro_RestartI2C()
**
** This function generates an I2C restart condition
**
** Inputs:  None
**
** Returns:  None
*/
void fnI2C_CoPro_RestartI2C( void )
{
   RestartI2C1();
   while( COPRO_RESTART_ENABLE != CLEAR )
   {
      /*Do nothing*/
   }
}

/*----------------------------------------------------------------------------
** Function: fnI2C_CoPro_ReadByte()
**
** This function reads a single byte from the Co-Processor
**
** Inputs:  None
**
** Returns:  returns a byte to the pointer ByteLocation
*/
void fnI2C_CoPro_ReadByte( UINT8 *ByteLocation )
{
   *ByteLocation = MasterReadI2C1();
   while( COPRO_TX_STATUS != CLEAR )
   {
      /*Do Nothing*/
   }
}

/*----------------------------------------------------------------------------
** Function: fnI2C_CoPro_ReadBytesAck()
**
** This function reads multiple bytes from the co processor
**
** Inputs:  ByteCount = number of bytes to read
**
** Returns:  BytesLocation read bytes
*/
void fnI2C_CoPro_ReadBytesAck( UINT8 *BytesLocation, UINT8 ByteCount )
{
   UINT8 i;

   for( i=0; i<ByteCount; i++ )
   {
      /* read next byte */
      fnI2C_CoPro_ReadByte( &BytesLocation[i] );

      if( i == (ByteCount - 1) )
      {
         
         NotAckI2C1();
      }
      else
      {
         /* Send ack data bit */
         AckI2C1();
      }

      /* Wait for ack to complete */
      while( COPRO_ACK_ENABLE != CLEAR )
      {
         /*Do Nothing*/
      }
   }
}

/*----------------------------------------------------------------------------
** Function: fnI2C_CoPro_ReadBytes()
**
** This function reads multiple bytes from the co processor, and allows the
** caller to choose whether to send and ACK or NACK after the last byte.
**
** Inputs:  ByteCount = number of bytes to read
**
** Returns:  BytesLocation read bytes
*/
void fnI2C_CoPro_ReadBytes( UINT8 *BytesLocation, UINT8 ByteCount, BOOL Ack )
{
   UINT8 i;

   for( i=0; i<ByteCount; i++ )
   {
      /* read next byte */
      fnI2C_CoPro_ReadByte( &BytesLocation[i] );

      if( (i == (ByteCount - 1)) && (Ack == FALSE) )
      {

         NotAckI2C1();
      }
      else
      {
         /* Send ack data bit */
         AckI2C1();
      }

      /* Wait for ack to complete */
      while( COPRO_ACK_ENABLE != CLEAR )
      {
         /*Do Nothing*/
      }
   }
}


/*----------------------------------------------------------------------------
** Function: fnI2C_CoPro_CheckAck()
**
** This function looks for an I2C ACK from the slave device
**
** Inputs:  None
**
** Returns: TRUE: ACK, FALSE: NOACK
*/
BOOL fnI2C_CoPro_CheckAck( void )
{
   BOOL ReturnState = FALSE;

   if( COPRO_ACK_STATUS == CLEAR )
   {
      ReturnState = TRUE;
   }

   return ReturnState;
}


/*************************************************************************
**    This section provides the low level functions for to control
**    The I2C2 peripheral
**
**************************************************************************/


/*----------------------------------------------------------------------------
** Function: fnI2C_SecMem_OpenI2C()
**
** This function configures and opens I2C2
**
** Inputs:  None
**
** Returns:  None
*/
void fnI2C_SecMem_OpenI2C( void )
{
   /* Setup the I2C config register and enable the port */
   OpenI2C2( I2CEN | DISSLW | ACKDT, I2C_BAUD_400K );
   /* wait for the port to go idle */
   IdleI2C2();
}

/*----------------------------------------------------------------------------
** Function: fnI2C_SecMem_CloseI2C()
**
** This function closes the I2C2 peripheral
**
** Inputs:  None
**
** Returns:  None
*/
void fnI2C_SecMem_CloseI2C( void )
{
   /* wait for the port to go idle */
   IdleI2C2();
   CloseI2C2();
}

/*----------------------------------------------------------------------------
** Function: fnI2C_SecMem_StartI2C()
**
** This function starts the Secure Memory I2C communications
**
** Inputs:  None
**
** Returns:  None
*/
void fnI2C_SecMem_StartI2C( void )
{
   StartI2C2();
   while( SECMEM_ENABLE != CLEAR )
   {
      /*do nothing*/
   }
}

/*----------------------------------------------------------------------------
** Function: fnI2C_SecMem_StopI2C()
**
** This function stops the Secure Memory I2C communications and
** changes the I2C peripheral state to idle
**
** Inputs:  None
**
** Returns:  None
*/
void fnI2C_SecMem_StopI2C( void )
{
   StopI2C2();
   while( SECMEM_IDLE != CLEAR )
   {
      /*do nothing*/
   }
   /* wait for the port to go idle */
   IdleI2C2();
}

/*----------------------------------------------------------------------------
** Function: fnI2C_SecMem_WriteByte()
**
** This function writes a single byte to the secure memory
** If a bus collision is detected the function will retry the write up to
** "RETRY_COUNT" number of times.
**
** Inputs:  Data to write to the secure memory
**
** Returns: None
**
*/
void fnI2C_SecMem_WriteByte( UINT8 SecMemWriteData )
{
   UINT8 CollisionRetry             = RETRY_COUNT;
   INT8  I2CWriteStatus             = 0;

   /* If an I2C bus collision occurs retry up to "RETRY_COUNT" times */
   do
   {
      if( SECMEM_WR_COL == SET )
      {
         SECMEM_WR_COL = CLEAR;
         SECMEM_I2C_EN = CLEAR;
         SECMEM_I2C_EN = SET;
      }

      /* Write the data to the secure memory */
      I2CWriteStatus = MasterWriteI2C2( SecMemWriteData );
      while( SECMEM_TX_STATUS != CLEAR )
      {
         /*do nothing*/
      }

      CollisionRetry--;

   }while( (CollisionRetry > 0) && (I2CWriteStatus == I2C_WRITE_COLLISION) );

   /* Check to see if an I2C bus collision occurred */
   if( I2CWriteStatus == I2C_WRITE_COLLISION )
   {
      /* Display an error number to show the I2C has failed */
      fnHWF_IndicateError( SEG_DISP_SECMEM_WR_BYTE_FLD );
   }
}

/*----------------------------------------------------------------------------
** This function writes several bytes to the secure memory
**
** Inputs:  Pointer to data to write to the secure memory
**          Number of bytes to write.
**
** Returns: None
**
*/
void fnI2C_SecMem_WriteBytes( const UINT8 * data,  UINT16 numBytes)
{
   UINT16 i;
   
   for (i = 0; i < numBytes; i++)
   {
      fnI2C_SecMem_WriteByte( data[i] );
   }
}



/*----------------------------------------------------------------------------
** Function: fnI2C_SecMem_CheckAck()
**
** This function looks for an I2C ACK from the slave device
**
** Inputs:  None
**
** Returns: TRUE: ACK, FALSE: NOACK
*/
BOOL fnI2C_SecMem_CheckAck( void )
{
   BOOL ReturnState = FALSE;

   if( SECMEM_ACK_STATUS == CLEAR )
   {
      ReturnState = TRUE;
   }

   return ReturnState;
}

/*----------------------------------------------------------------------------
** Function: fnI2C_SecMem_CheckAck()
**
** This function generates an I2C bus Not Acknowledge condition
**
** Inputs:  None
**
** Returns: None
*/
void fnI2C_SecMem_SendNoAck( void )
{
   SECMEM_SEND_ACK = SET;
   SECMEM_ACK_ENABLE = SET;
}

/*----------------------------------------------------------------------------
** Function: fnI2C_SecMem_RestartI2C()
**
** This function generates an I2C restart condition
**
** Inputs:  None
**
** Returns: None
*/
void fnI2C_SecMem_RestartI2C( void )
{
   RestartI2C2();
   while( SECMEM_RESTART_ENABLE != CLEAR )
   {
      /*Do nothing*/
   }
}


/*----------------------------------------------------------------------------
** Function: fnI2C_SecMem_ReadByte()
**
** This function reads a single byte from a secure memory IC
**
** Inputs:  None
**
** Returns:  ByteLocation = read byte
**
*/
void fnI2C_SecMem_ReadByte( UINT8 *ByteLocation )
{
   *ByteLocation = MasterReadI2C2();
   while( SECMEM_TX_STATUS != CLEAR )
   {
      /*Do Nothing*/
   }
}

/*----------------------------------------------------------------------------
** Function: fnI2C_SecMem_ReadBytes()
**
** This function reads multiple bytes from a secure memory IC
**
** Inputs:  ByteCount = number of bytes to read
**
** Returns:  BytesLocation = read bytes
**
*/
void fnI2C_SecMem_ReadBytes( UINT8 *BytesLocation, UINT8 ByteCount )
{
   UINT8 i;

   for( i=0; i<ByteCount; i++ )
   {
      /* Read the next byte */
      fnI2C_SecMem_ReadByte( &BytesLocation[i] );

      /* Send a NoAck bit after reading the last byte */
      if( i != (ByteCount - 1) )
      {
         AckI2C2();
         while( SECMEM_ACK_ENABLE != CLEAR )
         {
            /*Do Nothing*/
         }
      }
   }

   NotAckI2C2();
   while( SECMEM_ACK_ENABLE != CLEAR )
   {
      /*Do Nothing*/
   }
}



/*************************************************************************
**    This section provides the low level functions to control
**    The I2C3 peripheral
**
**************************************************************************/

/*----------------------------------------------------------------------------
** Function: fnI2C_SegDisp_OpenI2C()
**
** This function configures and opens I2C3
**
** Inputs:  None
**
** Returns: None
*/
void fnI2C_SegDisp_OpenI2C( void )
{
   /* Setup the I2C config register and enable the port */
   OpenI2C3( I2CEN | DISSLW | ACKDT, I2C_BAUD_1M );
   /* wait for the port to go idle */
   IdleI2C3();
}

/*----------------------------------------------------------------------------
** Function: fnI2C_SegDisp_StartI2C()
**
** This function starts the 7 segment LED driver comms
**
** Inputs:  None
**
** Returns: None
*/
static void fnI2C_SegDisp_StartI2C( void )
{
   StartI2C3();
   while( SEGDISP_ENABLE != CLEAR )
   {
      /*do nothing*/
   }
}

/*----------------------------------------------------------------------------
** Function: fnI2C_SegDisp_StopI2C()
**
** This function stops the7 segment LED driver I2C communications and
** waits for the I2C peripheral state to go idle
**
** Inputs:  None
**
** Returns: None
*/
static void fnI2C_SegDisp_StopI2C( void )
{
   StopI2C3();
   while( SEGDISP_IDLE != CLEAR )
   {
      /*do nothing*/
   }
   /* wait for the port to go idle */
   IdleI2C3();
}


/*----------------------------------------------------------------------------
** Function: fnSegDispI2CWriteBytes()
**
** This function writes multiple bytes to the 7 segment LED driver IC
**
** Inputs:  *WriteData, ByteCount
**
** Returns:  None
*/
void fnI2C_SegDispI2CWriteBytes( const UINT8 *WriteData, UINT8 ByteCount )
{
   /* The status of the I2C module */
   INT8 I2CWriteStatus              = 0;
   UINT8 WriteDataIndx              = 0;

   /* Send the start condition */
   fnI2C_SegDisp_StartI2C();

   /* Send the bytes */
   while( (WriteDataIndx < ByteCount) &&
           (I2CWriteStatus != I2C_WRITE_COLLISION) )
   {
      /* Write the next byte to the display IC */
      I2CWriteStatus = MasterWriteI2C3( WriteData[WriteDataIndx] );
      
      /* Wait for the transmit to complete */
      while( SEGDISP_TX_STATUS != CLEAR )
      {
         /*Do nothing*/
      }
      /* Wait for an ACK */
      while( SEGDISP_ACK_STATUS == NoAck )
      {
         /*Do Nothing*/
      }

      if( SEGDISP_WR_COL == SET )
      {
         SEGDISP_WR_COL = CLEAR;
         SEGDISP_I2C_EN = CLEAR;
         SEGDISP_I2C_EN = SET;
      }
      else
      {
         WriteDataIndx++;
      }
   }

   /* Send the stop condition */
   fnI2C_SegDisp_StopI2C();
}

/*----------------------------------------------------------------------------
** Function: fnI2C_SegDisp_ReadyCheck()
**
** This function is called to cause the system to wait until the 7 seg display
** is ready. The 7 seg display has separate brown-out hardware from the PIC,
** so it is essential to check the display is ready before configuration.
**
** Inputs:  None
**
** Returns: None
*/
/*lint -efunc(534,fnI2C_SegDisp_ReadyCheck) */
/* remove warning: */
/* "Ignoring return value of function 'MasterWriteI2C3(unsigned char)'" */
void fnI2C_SegDisp_ReadyCheck( const UINT8 WriteAddr )
{
   static const UINT8 ACK_WAIT_TIME = 32;
   UINT8 AckWaitCnt                 = 0;
   BOOL DispReady                   = FALSE;

   while( DispReady == FALSE )
   {
      AckWaitCnt = 0;
      /* Send the start condition */
      fnI2C_SegDisp_StartI2C();
      /* Send the I2C device addr byte */
      /* Returned value not used, as write collision bit is checked later */
      MasterWriteI2C3( WriteAddr );

      /* Wait for the transmit to complete */
      while( SEGDISP_TX_STATUS != CLEAR )
      {
         /*Do Nothing*/
      }
      /* Wait for an ACK */
      while( (SEGDISP_ACK_STATUS == NoAck) && (AckWaitCnt < ACK_WAIT_TIME) )
      {
         /* Increment the Ack wait counter */
         AckWaitCnt++;
      }
      /* Check for a write collision */
      if( SEGDISP_WR_COL == SET )
      {
         /* If a collision occured reset the I2C port */
         SEGDISP_WR_COL = CLEAR;
         SEGDISP_I2C_EN = CLEAR;
         SEGDISP_I2C_EN = SET;
      }
      /* Check if waiting for ACK took too long */
      else if( AckWaitCnt >= ACK_WAIT_TIME )
      {
         SEGDISP_I2C_EN = CLEAR;
         SEGDISP_I2C_EN = SET;
      }
      else
      {
         /* The display is ready so set a flag to exit the loop */
         DispReady = TRUE;
      }
      /* Send the stop condition */
      fnI2C_SegDisp_StopI2C();
   }
}
