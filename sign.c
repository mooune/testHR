/*
 * File: sign.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:38:36
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getPulseTemporal.h"
#include "sign.h"

/* Function Definitions */

/*
 * Arguments    : double x_data[]
 *                int x_size[1]
 * Return Type  : void
 */
void b_sign(double x_data[], int x_size[1])
{
  int i5;
  int k;
  i5 = x_size[0];
  for (k = 0; k < i5; k++) {
    if (x_data[k] < 0.0) {
      x_data[k] = -1.0;
    } else if (x_data[k] > 0.0) {
      x_data[k] = 1.0;
    } else {
      if (x_data[k] == 0.0) {
        x_data[k] = 0.0;
      }
    }
  }
}

/*
 * File trailer for sign.c
 *
 * [EOF]
 */
