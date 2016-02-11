/* 
 * File:   ENCODE1Peripheral.h
 * Author: Luke
 *
 * Created on 28 January 2016, 23:57
 */

#ifndef ENCODE1PERIPHERAL_H
#define	ENCODE1PERIPHERAL_H


//Function to read a value directly from the peripheral
char ReadENCODE1();

//Functions to read and write to the peripheral's buffer
int WriteENCODE1Buffer(char Data);
char* ReadENCODE1Buffer(int Count);

int ReadENCODE1Integral();
int ResetENCODE1Integral();

//Functions to Initiate / Clear
int InitiateENCODE1();
int ClearENCODE1Buffer();

#endif