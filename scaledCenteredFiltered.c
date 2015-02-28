/*
 * File: scaledCenteredFiltered.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:39:25
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "scaledCenteredFiltered.h"

/* Function Definitions */

/*
 * This function takes a buffer of 160 elements and apply
 *   a scaling of the buffer and then a low pass filter that has been created using the fdatool
 *   results have been exported into the worskpace, and then copied into a
 *   vector
 * Arguments    : const double datas[160]
 *                double b_scaledCenteredFiltered[128]
 * Return Type  : void
 */
void scaledCenteredFiltered(const double datas[160], double
  b_scaledCenteredFiltered[128])
{
  int ixstart;
  double mtmp;
  int ix;
  boolean_T exitg5;
  double b_mtmp;
  boolean_T exitg4;
  boolean_T exitg3;
  boolean_T exitg2;
  double c_mtmp;
  boolean_T exitg1;
  double scaledAndCentered[160];
  double filteredSignal[160];
  static const double dv0[31] = { -0.000832165505960179, -0.00274010224244439,
    -0.00264119576278684, 0.00285995644394177, 0.00858528972590101,
    0.00247356735691805, -0.0140462253144697, -0.0161648518695173,
    0.012047563740566, 0.0377290988119295, 0.00779065491788247,
    -0.0622450202583689, -0.0649458346068803, 0.0818635331438427,
    0.303112165988291, 0.410625144658028, 0.303112165988291, 0.0818635331438427,
    -0.0649458346068803, -0.0622450202583689, 0.00779065491788247,
    0.0377290988119295, 0.012047563740566, -0.0161648518695173,
    -0.0140462253144697, 0.00247356735691805, 0.00858528972590101,
    0.00285995644394177, -0.00264119576278684, -0.00274010224244439,
    -0.000832165505960179 };

  ixstart = 1;
  mtmp = datas[0];
  if (rtIsNaN(datas[0])) {
    ix = 2;
    exitg5 = false;
    while ((!exitg5) && (ix < 161)) {
      ixstart = ix;
      if (!rtIsNaN(datas[ix - 1])) {
        mtmp = datas[ix - 1];
        exitg5 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 160) {
    while (ixstart + 1 < 161) {
      if (datas[ixstart] > mtmp) {
        mtmp = datas[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  b_mtmp = datas[0];
  if (rtIsNaN(datas[0])) {
    ix = 2;
    exitg4 = false;
    while ((!exitg4) && (ix < 161)) {
      ixstart = ix;
      if (!rtIsNaN(datas[ix - 1])) {
        b_mtmp = datas[ix - 1];
        exitg4 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 160) {
    while (ixstart + 1 < 161) {
      if (datas[ixstart] < b_mtmp) {
        b_mtmp = datas[ixstart];
      }

      ixstart++;
    }
  }

  if (mtmp != b_mtmp) {
    ixstart = 1;
    mtmp = datas[0];
    if (rtIsNaN(datas[0])) {
      ix = 2;
      exitg3 = false;
      while ((!exitg3) && (ix < 161)) {
        ixstart = ix;
        if (!rtIsNaN(datas[ix - 1])) {
          mtmp = datas[ix - 1];
          exitg3 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < 160) {
      while (ixstart + 1 < 161) {
        if (datas[ixstart] < mtmp) {
          mtmp = datas[ixstart];
        }

        ixstart++;
      }
    }

    ixstart = 1;
    b_mtmp = datas[0];
    if (rtIsNaN(datas[0])) {
      ix = 2;
      exitg2 = false;
      while ((!exitg2) && (ix < 161)) {
        ixstart = ix;
        if (!rtIsNaN(datas[ix - 1])) {
          b_mtmp = datas[ix - 1];
          exitg2 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < 160) {
      while (ixstart + 1 < 161) {
        if (datas[ixstart] > b_mtmp) {
          b_mtmp = datas[ixstart];
        }

        ixstart++;
      }
    }

    ixstart = 1;
    c_mtmp = datas[0];
    if (rtIsNaN(datas[0])) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix < 161)) {
        ixstart = ix;
        if (!rtIsNaN(datas[ix - 1])) {
          c_mtmp = datas[ix - 1];
          exitg1 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < 160) {
      while (ixstart + 1 < 161) {
        if (datas[ixstart] < c_mtmp) {
          c_mtmp = datas[ixstart];
        }

        ixstart++;
      }
    }

    b_mtmp -= c_mtmp;
    for (ixstart = 0; ixstart < 160; ixstart++) {
      scaledAndCentered[ixstart] = 2.0 * ((datas[ixstart] - mtmp) / b_mtmp - 0.5);
    }
  } else {
    memset(&scaledAndCentered[0], 0, 160U * sizeof(double));
  }

  memset(&filteredSignal[0], 0, 160U * sizeof(double));
  for (ixstart = 0; ixstart < 31; ixstart++) {
    for (ix = ixstart; ix + 1 < 161; ix++) {
      filteredSignal[ix] += dv0[ixstart] * scaledAndCentered[ix - ixstart];
    }
  }

  memcpy(&b_scaledCenteredFiltered[0], &filteredSignal[32], sizeof(double) << 7);
}

/*
 * File trailer for scaledCenteredFiltered.c
 *
 * [EOF]
 */
