/*
 * File: var.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:38:36
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getPulseTemporal.h"
#include "var.h"

/* Function Definitions */

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 * Return Type  : double
 */
double var(const double x_data[], const int x_size[2])
{
  double y;
  int n;
  int ix;
  double xbar;
  int k;
  double r;
  int b_x_size;
  n = x_size[1] - 2;
  if (x_size[1] == 0) {
    y = 0.0;
  } else {
    ix = 0;
    xbar = x_data[0];
    for (k = 0; k <= n; k++) {
      ix++;
      xbar += x_data[ix];
    }

    xbar /= (double)x_size[1];
    ix = 0;
    r = x_data[0] - xbar;
    y = r * r;
    for (k = 0; k <= n; k++) {
      ix++;
      r = x_data[ix] - xbar;
      y += r * r;
    }

    if (x_size[1] > 1) {
      b_x_size = x_size[1] - 1;
    } else {
      b_x_size = x_size[1];
    }

    y /= (double)b_x_size;
  }

  return y;
}

/*
 * File trailer for var.c
 *
 * [EOF]
 */
