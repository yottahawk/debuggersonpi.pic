/* 
 * File:   I2C2.h
 * Author: Harry
 * 
 * Comments:
 *
 * Created on February 17, 2016, 1:33 AM
 */

#ifndef debuggersonpi_pic_I2C2_h
#define debuggersonpi_pic_I2C2_h

//////////////////////////////////////INCLUDES//////////////////////////////////

#include "xc.h"
#define USE_AND_OR
#include <i2c.h>            // 24f peripheral library

#include "led.h"

//////////////////////////////////////DEFINES///////////////////////////////////

////////////////////////////////TYPEDEFS,ENUMS,STRUCTS//////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

///////////////////////////////FUNCTION DECLARATIONS////////////////////////////

// PRIMO I2C code using PIC24F peripheral library
void periph_OpenI2C2( void );
void periph_CloseI2C2( void );
void periph_StartI2C2( void );
void periph_StopI2C2( void );
void periph_WriteByteI2C2( const UINT8 CoProWriteData );
void periph_WriteBytesI2C2( const UINT8 * data,  UINT16 numBytes);
void periph_RestartI2C2( void );
void periph_ReadByteI2C2( UINT8 *ByteLocation );
void periph_ReadBytesAckI2C2( UINT8 *BytesLocation, UINT8 ByteCount );
void periph_ReadBytesI2C2( UINT8 *BytesLocation, UINT8 ByteCount, BOOL Ack );
BOOL periph_CheckAckI2C2( void );

////////////////////////////////////////////////////////////////////////////////
#endif //debuggersonpi_pic_I2C2_h
