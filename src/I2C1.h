/* 
 * File:   I2C1.h
 * Author: Harry
 * 
 * Comments:
 *
 * Created on February 15, 2016, 10:10 PM
 */

#ifndef debuggersonpi_pic_I2C1_h
#define debuggersonpi_pic_I2C1_h

//////////////////////////////////////INCLUDES//////////////////////////////////

#include "xc.h"
#define USE_AND_OR
#include <i2c.h>            // 24f peripheral library

#include "led.h"

//////////////////////////////////////DEFINES///////////////////////////////////

////////////////////////////////TYPEDEFS,ENUMS,STRUCTS//////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

///////////////////////////////FUNCTION DECLARATIONS////////////////////////////

void I2C1_init(int Baud_Rate);
void I2C1_resetbus();
void I2C1_start();
void I2C1_repeatstart();
unsigned char I2C1_send_byte(unsigned char data);
unsigned char I2C1_read_ack();
unsigned char I2C1_read_no_ack();

// PRIMO I2C code using PIC24F peripheral library
void periph_OpenI2C1( void );
void periph_CloseI2C1( void );
void periph_StartI2C1( void );
void periph_StopI2C1( void );
void periph_WriteByteI2C1( const UINT8 CoProWriteData );
void periph_WriteBytesI2C1( const UINT8 * data,  UINT16 numBytes);
void periph_RestartI2C1( void );
void periph_ReadByteI2C1( UINT8 *ByteLocation );
void periph_ReadBytesAckI2C1( UINT8 *BytesLocation, UINT8 ByteCount );
void periph_ReadBytesI2C1( UINT8 *BytesLocation, UINT8 ByteCount, BOOL Ack );
BOOL periph_CheckAckI2C1( void );

////////////////////////////////////////////////////////////////////////////////
#endif //debuggersonpi_pic_I2C1_h
