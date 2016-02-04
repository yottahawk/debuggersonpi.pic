/* 
 * File:   OpenLoop.h
 * Author: Luke
 *
 * Created on 03 February 2016, 23:24
 */

#ifndef OPENLOOP_H
#define	OPENLOOP_H

#ifdef	__cplusplus
extern "C" {
#endif

//declarations for open loop functions
void ol_forward();
void ol_reverse();
void ol_fwd_left();
void ol_fwd_right();
void ol_rev_left();
void ol_rev_right();

#ifdef	__cplusplus
}
#endif

#endif	/* OPENLOOP_H */

