/* 
 * File:   I2C2.c
 * Author: Harry
 *
 * Created on February 17, 2016, 1:33 AM
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "I2C2.h"

/////////////////////////////////////DEFINES////////////////////////////////////

#define COMPASS_START_ENABLE I2C1CONbits.SEN
#define COMPASS_IDLE I2C1CONbits.PEN
#define COMPASS_TX_STATUS I2C1STATbits.TRSTAT
#define COMPASS_RESTART_ENABLE I2C1CONbits.RSEN
#define COMPASS_ACK_ENABLE I2C1CONbits.ACKEN
#define COMPASS_ACK_STATUS I2C1STATbits.ACKSTAT
#define COMPASS_WR_COL I2C1STATbits.IWCOL
#define COMPASS_I2C_EN I2C1CONbits.I2CEN

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

/* I2C baud rates for a system clock of 8 Mhz*/
static const unsigned int I2C_BAUD_100K = 0x000F; /* I2C baud rate 100KHz Setting */

/* number of times to retry if a write collision is detected */
static const UINT8 RETRY_COUNT          = 3;
/* "MasterWriteI2C1" returns -1 if a write collision occurs */
static const INT8 I2C_WRITE_COLLISION   = -1;
/* ACKSTAT register bit = 1 for NACK detected last */
static const UINT8 NoAck                = 1;

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////



/*----------------------------------------------------------------------------
** Function: periph_OpenI2C()
**
** This function configures and opens I2C1
**
** Inputs:  None
**
** Returns:  None
*/
void periph_OpenI2C2( void )
{
   /* Setup the I2C config register and enable the port */
   OpenI2C2( I2C_ON | I2C_SLW_DIS | I2C_ACK , I2C_BAUD_100K );
   /* wait for the port to go idle */
   IdleI2C2();
}

/*----------------------------------------------------------------------------
** Function: periph_CloseI2C()
**
** This function closes the I2C1 peripheral
**
** Inputs:  None
**
** Returns:  None
*/
void periph_CloseI2C2( void )
{
   /* wait for the port to go idle */
   IdleI2C2();
   CloseI2C2();
}

/*----------------------------------------------------------------------------
** Function: periph_StartI2C()
**
** This function starts the Co-Processor I2C communications
**
** Inputs:  None
**
** Returns:  None
*/
void periph_StartI2C2( void )
{
   StartI2C2();
   while( COMPASS_START_ENABLE != CLEAR )
   {
      /*do nothing*/
   }
}

/*----------------------------------------------------------------------------
** Function: periph_StopI2C()
**
** This function stops the Co-Processor I2C communications and
** changes the I2C peripheral state to idle
**
** Inputs:  None
**
** Returns:  None
*/
void periph_StopI2C2( void )
{
   StopI2C1();
   while( COMPASS_IDLE != CLEAR )
   {
      /*do nothing*/
   }
   /* wait for the port to go idle */
   IdleI2C2();
}

/*----------------------------------------------------------------------------
** Function: periph_WriteByte()
**
** This function writes a single byte to the Co-Processor
** If a bus collision is detected the function will retry the write up to
** "RETRY_COUNT" number of times.
**
** Inputs:   Data to write to the Co_processor
**
** Returns:  NOne
*/
void periph_WriteByteI2C2( const UINT8 CoProWriteData )
{
   UINT8 CollisionRetry             = RETRY_COUNT;
   INT8  I2CWriteStatus             = 0;

   /* If an I2C bus collision occurs retry up to "RETRY_COUNT" times */
   do
   {
      if( COMPASS_WR_COL == SET )
      {
         COMPASS_WR_COL = CLEAR;
         COMPASS_WR_COL = CLEAR;
         COMPASS_WR_COL = SET;
      }

      /* Write the data to the Co-Processor*/
      I2CWriteStatus = MasterWriteI2C2( CoProWriteData );
      while( COMPASS_TX_STATUS != CLEAR )
      {
         /*do nothing*/
      }

      CollisionRetry--;

   }while( (CollisionRetry > 0) && (I2CWriteStatus == I2C_WRITE_COLLISION) );

   /* Check to see if an I2C bus collision occurred */
   if( I2CWriteStatus == I2C_WRITE_COLLISION )
   {
      /* Display an error number to show the I2C has failed */
       
      // fnHWF_IndicateError( SEG_DISP_COPRO_WR_BYTE_FLD );
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
void periph_WriteBytesI2C2( const UINT8 * data,  UINT16 numBytes)
{
   UINT16 i;

   for (i = 0; i < numBytes; i++)
   {
      periph_WriteByteI2C2( data[i] );
   }
}

/*----------------------------------------------------------------------------
** Function: periph_RestartI2C()
**
** This function generates an I2C restart condition
**
** Inputs:  None
**
** Returns:  None
*/
void periph_RestartI2C2( void )
{
   RestartI2C2();
   while( COMPASS_RESTART_ENABLE != CLEAR )
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
void periph_ReadByteI2C2( UINT8 *ByteLocation )
{
   *ByteLocation = MasterReadI2C2();
   while( COMPASS_TX_STATUS != CLEAR )
   {
      /*Do Nothing*/
   }
}

/*----------------------------------------------------------------------------
** Function: periph_ReadBytesAck()
**
** This function reads multiple bytes from the co processor
**
** Inputs:  ByteCount = number of bytes to read
**
** Returns:  BytesLocation read bytes
*/
void periph_ReadBytesAckI2C2( UINT8 *BytesLocation, UINT8 ByteCount )
{
   UINT8 i;

   for( i=0; i<ByteCount; i++ )
   {
      /* read next byte */
      periph_ReadByteI2C2( &BytesLocation[i] );

      if( i == (ByteCount - 1) )
      {
         
         NotAckI2C2();
      }
      else
      {
         /* Send ack data bit */
         AckI2C2();
      }

      /* Wait for ack to complete */
      while( COMPASS_ACK_ENABLE != CLEAR )
      {
         /*Do Nothing*/
      }
   }
}

/*----------------------------------------------------------------------------
** Function: periph_ReadBytes()
**
** This function reads multiple bytes from the co processor, and allows the
** caller to choose whether to send and ACK or NACK after the last byte.
**
** Inputs:  ByteCount = number of bytes to read
**
** Returns:  BytesLocation read bytes
*/
void periph_ReadBytesI2C2( UINT8 *BytesLocation, UINT8 ByteCount, BOOL Ack )
{
   UINT8 i;

   for( i=0; i<ByteCount; i++ )
   {
      /* read next byte */
      periph_ReadByteI2C2( &BytesLocation[i] );

      if( (i == (ByteCount - 1)) && (Ack == FALSE) )
      {

         NotAckI2C2();
      }
      else
      {
         /* Send ack data bit */
         AckI2C2();
      }

      /* Wait for ack to complete */
      while( COMPASS_ACK_ENABLE != CLEAR )
      {
         /*Do Nothing*/
      }
   }
}

/*----------------------------------------------------------------------------
** Function: periph_CheckAck()
**
** This function looks for an I2C ACK from the slave device
**
** Inputs:  None
**
** Returns: TRUE: ACK, FALSE: NOACK
*/
BOOL periph_CheckAckI2C2( void )
{
   BOOL ReturnState = FALSE;

   if( COMPASS_ACK_STATUS == CLEAR )
   {
      ReturnState = TRUE;
   }

   return ReturnState;
}