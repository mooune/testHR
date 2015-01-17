/*
 * File: scaleAndCenter.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 17-Jan-2015 15:29:17
 */

/* Include Files */
#include "scaleAndCenter.h"

/* Function Definitions */

/*
 * Arguments    : const double datas[128]
 *                double scaledAndCentered[128]
 * Return Type  : void
 */
void scaleAndCenter(const double datas[128], double scaledAndCentered[128])
{
  double mtmp;
  double b_mtmp;
  int ix;
  double c_mtmp;
  double filteredSignal[128];
  int j;
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

  mtmp = datas[0];
  b_mtmp = datas[0];
  for (ix = 0; ix < 127; ix++) {
    if (datas[ix + 1] > mtmp) {
      mtmp = datas[ix + 1];
    }

    if (datas[ix + 1] < b_mtmp) {
      b_mtmp = datas[ix + 1];
    }
  }

  if (mtmp != b_mtmp) {
    mtmp = datas[0];
    b_mtmp = datas[0];
    c_mtmp = datas[0];
    for (ix = 0; ix < 127; ix++) {
      if (datas[ix + 1] < mtmp) {
        mtmp = datas[ix + 1];
      }

      if (datas[ix + 1] > b_mtmp) {
        b_mtmp = datas[ix + 1];
      }

      if (datas[ix + 1] < c_mtmp) {
        c_mtmp = datas[ix + 1];
      }
    }

    b_mtmp -= c_mtmp;
    for (ix = 0; ix < 128; ix++) {
      scaledAndCentered[ix] = 2.0 * ((datas[ix] - mtmp) / b_mtmp - 0.5);
    }
  } else {
    memset(&scaledAndCentered[0], 0, sizeof(double) << 7);
  }

  memset(&filteredSignal[0], 0, sizeof(double) << 7);
  for (ix = 0; ix < 31; ix++) {
    for (j = ix; j + 1 < 129; j++) {
      filteredSignal[j] += dv0[ix] * scaledAndCentered[j - ix];
    }
  }

  memcpy(&scaledAndCentered[0], &filteredSignal[0], sizeof(double) << 7);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void scaleAndCenter_initialize(void)
{
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void scaleAndCenter_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for scaleAndCenter.c
 *
 * [EOF]
 */
