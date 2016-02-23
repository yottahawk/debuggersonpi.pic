/* 
 * File:   hs_math.h
 * Author: Luke
 *
 * Created on 22 February 2016, 20:39
 */

#ifndef HS_MATH_H
#define	HS_MATH_H

#ifdef	__cplusplus
extern "C" {
#endif

//takes 2 dimensionless numbers as 16-bit integers and returns a value in degrees
// -180 < result < 180
int atan_int(int x, int y);


#ifdef	__cplusplus
}
#endif

#endif	/* HS_MATH_H */

