/* 
 * File:   hs_math.c
 * Author: Luke
 *
 */

/////////////////////////////////////INCLUDES///////////////////////////////////

#include "hs_math.h"

/////////////////////////////////////DEFINES////////////////////////////////////

//////////////////////////////////GLOBAL VARIABLES//////////////////////////////

//////////////////////////////TYPEDEFS,ENUMS,STRUCTS////////////////////////////

///////////////////////////////FUNCTION DEFINITIONS/////////////////////////////

int lookup(char val) {
    switch(val) {
        case 0:    return 0;
                    break;
        case 1:    return 1;
                    break;
        case 2:    return 1;
                    break;
        case 3:    return 3;
                    break;
        case 4:    return 4;
                    break;
        case 5:    return 4;
                    break;
        case 6:    return 5;
                    break;
        case 7:    return 6;
                    break;
        case 8:    return 7;
                    break;
        case 9:    return 8;
                    break;
        case 10:    return 9;
                    break;
        case 11:    return 10;
                    break;
        case 12:    return 11;
                    break;
        case 13:    return 11;
                    break;
        case 14:    return 12;
                    break;
        case 15:    return 13;
                    break;
        case 16:    return 14;
                    break;
        case 17:    return 15;
                    break;
        case 18:    return 15;
                    break;
        case 19:    return 16;
                    break;
        case 20:    return 18;
                    break;
        case 21:    return 18;
                    break;
        case 22:    return 19;
                    break;
        case 23:    return 20;
                    break;
        case 24:    return 20;
                    break;
        case 25:    return 21;
                    break;
        case 26:    return 22;
                    break;
        case 27:    return 23;
                    break;
        case 28:    return 24;
                    break;
        case 29:    return 25;
                    break;
        case 30:    return 25;
                    break;
        case 31:    return 26;
                    break;
        case 32:    return 27;
                    break;
        case 33:    return 27;
                    break;
        case 34:    return 28;
                    break;
        case 35:    return 29;
                    break;
        case 36:    return 30;
                    break;
        case 37:    return 30;
                    break;
        case 38:    return 31;
                    break;
        case 39:    return 31;
                    break;
        case 40:    return 32;
                    break;
        case 41:    return 32;
                    break;
        case 42:    return 33;
                    break;
        case 43:    return 34;
                    break;
        case 44:    return 35;
                    break;
        case 45:    return 35;
                    break;
        case 46:    return 36;
                    break;
        case 47:    return 36;
                    break;
        case 48:    return 37;
                    break;
        case 49:    return 37;
                    break;
        case 50:    return 38;
                    break;
        case 51:    return 38;
                    break;
        case 52:    return 39;
                    break;
        case 53:    return 39;
                    break;
        case 54:    return 40;
                    break;
        case 55:    return 40;
                    break;
        case 56:    return 41;
                    break;
        case 57:    return 41;
                    break;
        case 58:    return 42;
                    break;
        case 59:    return 43;
                    break;
        case 60:    return 43;
                    break;
        case 61:    return 44;
                    break;
        case 62:    return 44;
                    break;
        case 63:    return 45;
                    break;
        case 64:    return 45;
        			break;
        default:    return 0;
    }   
}

int atan_int(int x, int y) {
    //Lookup table based function: gives result in milli-degrees
    unsigned int absx = x;
    unsigned int absy = y;
    
    //check positivity - for smaller LUT x & y both positive
    char negx = 0;
    char negy = 0;
    if(x < 0) {
        absx = ~x+1;
        negx = 1;
    }
    if(y < 0) {
        absy = ~y+1;
        negy = 1;
    }
 
    //for reliable calculation x must be > y
    char swap = 0;
    if(absx < absy) {
        unsigned int temp = absy;
        absy = absx;
        absx = temp;
        swap = 1;
    }
    
    //cant compute atan if absx is 0
    if(absx == 0) return 0;
    
    unsigned long int numerator = absy << 6;
    char index = numerator / absx;     //index will now be between 0 and 64, giving 
    int degrees = lookup(index);
    
    //move back to appropriate quadrant
    if(swap) {
        degrees = 90-degrees;
    } 
    if (negx) {
        degrees = 180-degrees;
    }
    if (negy) {
        degrees = degrees*-1;
    }
    
    return degrees;
}