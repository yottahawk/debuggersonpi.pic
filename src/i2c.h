/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

void i2c_init(int Baud_Rate);
void i2c_resetbus();
void i2c_start();
void i2c_restart();

char send_i2c_byte(int data);
