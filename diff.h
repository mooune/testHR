/*
 * File: diff.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:38:36
 */

#ifndef __DIFF_H__
#define __DIFF_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "getPulseTemporal_types.h"

/* Function Declarations */
extern void b_diff(const double x_data[], const int x_size[2], double y_data[],
                   int y_size[2]);
extern void diff(const double x_data[], const int x_size[1], double y_data[],
                 int y_size[1]);

#endif

/*
 * File trailer for diff.h
 *
 * [EOF]
 */
