/*
 * File: diff.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:38:36
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getPulseTemporal.h"
#include "diff.h"

/* Function Definitions */

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
void b_diff(const double x_data[], const int x_size[2], double y_data[], int
            y_size[2])
{
  int b_x_size;
  int ixLead;
  int iyLead;
  double work_data_idx_0;
  int m;
  double tmp2;
  if (x_size[1] == 0) {
    y_size[0] = 1;
    y_size[1] = 0;
  } else {
    if (x_size[1] - 1 <= 1) {
      b_x_size = x_size[1] - 1;
    } else {
      b_x_size = 1;
    }

    if (b_x_size < 1) {
      y_size[0] = 1;
      y_size[1] = 0;
    } else {
      y_size[0] = 1;
      y_size[1] = x_size[1] - 1;
      if (!(x_size[1] - 1 == 0)) {
        ixLead = 1;
        iyLead = 0;
        work_data_idx_0 = x_data[0];
        for (m = 2; m <= x_size[1]; m++) {
          tmp2 = work_data_idx_0;
          work_data_idx_0 = x_data[ixLead];
          tmp2 = x_data[ixLead] - tmp2;
          ixLead++;
          y_data[iyLead] = tmp2;
          iyLead++;
        }
      }
    }
  }
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                double y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
void diff(const double x_data[], const int x_size[1], double y_data[], int
          y_size[1])
{
  int b_x_size;
  int ixLead;
  int iyLead;
  double work_data_idx_0;
  int m;
  double tmp2;
  if (x_size[0] == 0) {
    y_size[0] = 0;
  } else {
    if (x_size[0] - 1 <= 1) {
      b_x_size = x_size[0] - 1;
    } else {
      b_x_size = 1;
    }

    if (b_x_size < 1) {
      y_size[0] = 0;
    } else {
      y_size[0] = x_size[0] - 1;
      if (!(x_size[0] - 1 == 0)) {
        ixLead = 1;
        iyLead = 0;
        work_data_idx_0 = x_data[0];
        for (m = 2; m <= x_size[0]; m++) {
          tmp2 = work_data_idx_0;
          work_data_idx_0 = x_data[ixLead];
          tmp2 = x_data[ixLead] - tmp2;
          ixLead++;
          y_data[iyLead] = tmp2;
          iyLead++;
        }
      }
    }
  }
}

/*
 * File trailer for diff.c
 *
 * [EOF]
 */
