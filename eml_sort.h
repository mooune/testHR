/*
 * File: eml_sort.h
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:38:36
 */

#ifndef __EML_SORT_H__
#define __EML_SORT_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "getPulseTemporal_types.h"

/* Function Declarations */
extern void c_eml_sort(const double x_data[], const int x_size[1], double
  y_data[], int y_size[1]);
extern void eml_sort(const double x_data[], const int x_size[1], double y_data[],
                     int y_size[1], int idx_data[], int idx_size[1]);

#endif

/*
 * File trailer for eml_sort.h
 *
 * [EOF]
 */
