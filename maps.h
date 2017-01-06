/*
 * =====================================================================================
 *
 *       Filename:  maps.hpp
 *
 *        Version:  1.0
 *        Created:  12/12/2016 15:41:35
 *
 *
 * =====================================================================================
 */
#ifndef MAPS_H
#define MAPS_H

// Stack bounds 
void * getDebutStack(long pid); // debut stack proto
void * getFinStack(long pid);

// Program bound
void * getDebutProc(long pid);
void * getFinProc(long pid);

#endif
