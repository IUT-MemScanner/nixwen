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

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string>
/*fichier*/
#include <dirent.h>
/* isdigit */
#include <ctype.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "utils.hpp"

using namespace std;
// Stack bounds

void * getDebutStack(long pid);
void * getFinStack(long pid);

// Heap bounds
void * getDebutHeap(long pid);
void * getFinHeap(long pid);

void * getDebutData(long pid);
void * getFinData(long pid);

// Program bound
void * getDebutProc(long pid);
void * getFinProc(long pid);

#endif
