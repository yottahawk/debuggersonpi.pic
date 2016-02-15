/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef debuggersonpi_pic_i2c_h
#define debuggersonpi_pic_i2c_h

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "xc.h"

#include "led.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

////////////////////////////////FUNCTION DECLARATIONS///////////////////////////

void i2c_init(int Baud_Rate);
void i2c_resetbus();
void i2c_start();
void i2c_repeatstart();

unsigned char send_i2c_byte(unsigned char data);
unsigned char i2c_read_ack();
unsigned char i2c_read_no_ack();

#endif //debuggersonpi_pic_i2c_h

