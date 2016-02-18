/* 
 * File:   I2C1.c
 * Author: Harry
 *
 * Created on February 15, 2016, 10:09 PM
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "I2C1.h"

/////////////////////////////////////DEFINES////////////////////////////////////

 // 

#define COMPASS_START_ENABLE I2C1CONbits.SEN
#define COMPASS_IDLE I2C1CONbits.PEN
#define COMPASS_TX_STATUS I2C1STATbits.TRSTAT
#define COMPASS_RESTART_ENABLE I2C1CONbits.RSEN
#define COMPASS_ACK_ENABLE I2C1CONbits.ACKEN
#define COMPASS_ACK_STATUS I2C1STATbits.ACKSTAT
#define COMPASS_WR_COL I2C1STATbits.IWCOL
#define COMPASS_I2C_EN I2C1CONbits.I2CEN

/* I2C baud rates for a system clock of 8 Mhz*/
static const unsigned int I2C_BAUD_100K = 0x000F; /* I2C baud rate 100KHz Setting */

/* number of times to retry if a write collision is detected */
static const UINT8 RETRY_COUNT          = 3;
/* "MasterWriteI2C1" returns -1 if a write collision occurs */
static const INT8 I2C_WRITE_COLLISION   = -1;
/* ACKSTAT register bit = 1 for NACK detected last */
static const UINT8 NoAck                = 1;

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

void I2C1_resetbus()
{
    I2C1CONbits.RCEN        = 0;                // Disable receive as master
    IFS1bits.MI2C1IF        = 0;                // Clear interrupt
    I2C1STATbits.IWCOL      = 0;                // Reset write collision flag
    I2C1STATbits.BCL        = 0;                // Reset bus collision flag
    
    I2C1CONbits.PEN = 1;                        // initiate stop condition as master
    
    // wait for hardware clear of stop bit
    while (I2C1CONbits.PEN){}
    
    I2C1CONbits.RCEN        = 0;                // Disable receive as master
    IFS1bits.MI2C1IF        = 0;                // Clear interrupt
    I2C1STATbits.IWCOL      = 0;                // Reset write collision flag
    I2C1STATbits.BCL        = 0;                // Reset bus collision flag
}

void I2C1_init(int Baud_Rate)
{
    int clearbuffertemp;
    
    // Set baud rate using I2C1BRG
    // With Fosc = 4Mhz...
    // I2C1BRG = 39 -> 100kHz clock
    // I2C1BRG = 79 -> 50 kHz clock
    
    I2C1CONbits.I2CEN       = 0;                // Disable I2C mode
    
    I2C1BRG = Baud_Rate;                        // Set new baud rate
    I2C1CONbits.DISSLW      = 1;                // Disable slew rate control
    IFS1bits.MI2C1IF        = 0;                // Clear interrupt
    I2C1CONbits.I2CEN       = 1;                // Enable I2C mode
    
    clearbuffertemp         = I2C1RCV;          // read receive buffer to clear buffer
    I2C1_resetbus();                             // set bus to idle
}

void I2C1_start()
{
    I2C1CONbits.ACKDT       = 0;                // Reset any previous ack
    I2C1CONbits.SEN         = 1;                // Initiate start condition
    
    // Wait for the hardware to automatically clear the start bit
    while (I2C1CONbits.SEN){}                   
}

void I2C1_repeatstart()
{
   I2C1CONbits.RSEN = 1;                        //Initiate repeatedstart condition
    
   // Wait for hardware to automatically clear the reset bit
   while (I2C1CONbits.RSEN){}
}

unsigned char I2C1_send_byte(unsigned char data)
{
   while (I2C1STATbits.TBF){}                   // Wait for transmission to complete
  
   IFS1bits.MI2C1IF = 0;                        // Clear Interrupt
   I2C1TRN = data;                              // load the outgoing data byte

   // wait for transmission to complete
   while (I2C1STATbits.TRSTAT){};

   // Check for ACK from slave, abort if not found
   if (I2C1STATbits.ACKSTAT == 1) // Slave sends NACK
   {
      led_const_grn_on();
      return(1);
   }
   
   return(0);               // transmission completed successfully
}

unsigned char I2C1_read_ack()
{
   unsigned char temp = 0; 
   
   // Check lower 5 bits of I2C1CON register are all 0
   if (!(I2C1CON & 0x001F)){};
   
   //set I2C module to receive
   I2C1CONbits.RCEN = 1;
   
   while (I2C1CONbits.RCEN){};
   while (!I2C1STATbits.RBF){};
   temp = I2C1RCV; //get data from I2C1RCV register
   
   I2C1CONbits.ACKEN = 1;       // Ack
   
   //return data
   return temp;
}

unsigned char I2C1_read_no_ack()
{
   unsigned char temp = 0; 
    
   //set I2C module to receive
   I2C1CONbits.RCEN = 1;
   
   while (!I2C1STATbits.RBF){};
        
   temp = I2C1RCV; //get data from I2C1RCV register
   
   //return data
   return temp;
}

////////////////////////////////////////////////////////////////////////////////

/*----------------------------------------------------------------------------
** Function: periph_OpenI2C()
**
** This function configures and opens I2C1
**
** Inputs:  None
**
** Returns:  None
*/
void periph_OpenI2C1( void )
{
   /* Setup the I2C config register and enable the port */
   OpenI2C1( I2C_ON | I2C_SLW_DIS | I2C_ACK , I2C_BAUD_100K );
   /* wait for the port to go idle */
   IdleI2C1();
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
void periph_CloseI2C1( void )
{
   /* wait for the port to go idle */
   IdleI2C1();
   CloseI2C1();
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
void periph_StartI2C1( void )
{
   StartI2C1();
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
void periph_StopI2C1( void )
{
   StopI2C1();
   while( COMPASS_IDLE != CLEAR )
   {
      /*do nothing*/
   }
   /* wait for the port to go idle */
   IdleI2C1();
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
void periph_WriteByteI2C1( const UINT8 CoProWriteData )
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
      I2CWriteStatus = MasterWriteI2C1( CoProWriteData );
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
void periph_WriteBytesI2C1( const UINT8 * data,  UINT16 numBytes)
{
   UINT16 i;

   for (i = 0; i < numBytes; i++)
   {
      periph_WriteByteI2C1( data[i] );
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
void periph_RestartI2C1( void )
{
   RestartI2C1();
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
void periph_ReadByteI2C1( UINT8 *ByteLocation )
{
   *ByteLocation = MasterReadI2C1();
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
void periph_ReadBytesAckI2C1( UINT8 *BytesLocation, UINT8 ByteCount )
{
   UINT8 i;

   for( i=0; i<ByteCount; i++ )
   {
      /* read next byte */
      periph_ReadByteI2C1( &BytesLocation[i] );

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
void periph_ReadBytesI2C1( UINT8 *BytesLocation, UINT8 ByteCount, BOOL Ack )
{
   UINT8 i;

   for( i=0; i<ByteCount; i++ )
   {
      /* read next byte */
      periph_ReadByteI2C1( &BytesLocation[i] );

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
BOOL periph_CheckAckI2C1( void )
{
   BOOL ReturnState = FALSE;

   if( COMPASS_ACK_STATUS == CLEAR )
   {
      ReturnState = TRUE;
   }

   return ReturnState;
}

////////////////////////////////////////////////////////////////////////////////