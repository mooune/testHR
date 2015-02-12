/*
 * File: getPulseTemporal.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 31-Jan-2015 18:42:34
 */

#ifndef __GETPULSETEMPORAL_H__
#define __GETPULSETEMPORAL_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "getPulseTemporal_types.h"

/* Function Declarations */
extern unsigned char getPulseTemporal(const double channelOfInterest[128],
  double frameRate);
extern void getPulseTemporal_initialize(void);
extern void getPulseTemporal_terminate(void);

#endif

/*
 * File trailer for getPulseTemporal.h
 *
 * [EOF]
 */
