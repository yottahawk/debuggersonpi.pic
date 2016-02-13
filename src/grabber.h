/* 
 * File:   grabber.h
 * Author: Luke
 *
 * Created on 13 February 2016, 10:02
 */

#ifndef GRABBER_H
#define	GRABBER_H

#ifdef	__cplusplus
extern "C" {
#endif

    void OpenGRABBER();
    void CloseGRABBER();
    unsigned int ReadGRABBER();

#ifdef	__cplusplus
}
#endif

#endif	/* GRABBER_H */

