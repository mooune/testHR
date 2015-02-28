/*
 * File: mldivide.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:40:21
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "myPolyDetrend.h"
#include "mldivide.h"

/* Function Definitions */

/*
 * Arguments    : const double A[36]
 *                double B[6]
 * Return Type  : void
 */
void mldivide(const double A[36], double B[6])
{
  double b_A[36];
  signed char ipiv[6];
  int i5;
  int j;
  int c;
  int kAcol;
  int ix;
  double temp;
  int k;
  double s;
  int jy;
  int ijA;
  memcpy(&b_A[0], &A[0], 36U * sizeof(double));
  for (i5 = 0; i5 < 6; i5++) {
    ipiv[i5] = (signed char)(1 + i5);
  }

  for (j = 0; j < 5; j++) {
    c = j * 7;
    kAcol = 0;
    ix = c;
    temp = fabs(b_A[c]);
    for (k = 2; k <= 6 - j; k++) {
      ix++;
      s = fabs(b_A[ix]);
      if (s > temp) {
        kAcol = k - 1;
        temp = s;
      }
    }

    if (b_A[c + kAcol] != 0.0) {
      if (kAcol != 0) {
        ipiv[j] = (signed char)((j + kAcol) + 1);
        ix = j;
        kAcol += j;
        for (k = 0; k < 6; k++) {
          temp = b_A[ix];
          b_A[ix] = b_A[kAcol];
          b_A[kAcol] = temp;
          ix += 6;
          kAcol += 6;
        }
      }

      i5 = (c - j) + 6;
      for (jy = c + 1; jy + 1 <= i5; jy++) {
        b_A[jy] /= b_A[c];
      }
    }

    kAcol = c;
    jy = c + 6;
    for (k = 1; k <= 5 - j; k++) {
      temp = b_A[jy];
      if (b_A[jy] != 0.0) {
        ix = c + 1;
        i5 = (kAcol - j) + 12;
        for (ijA = 7 + kAcol; ijA + 1 <= i5; ijA++) {
          b_A[ijA] += b_A[ix] * -temp;
          ix++;
        }
      }

      jy += 6;
      kAcol += 6;
    }
  }

  for (kAcol = 0; kAcol < 5; kAcol++) {
    if (ipiv[kAcol] != kAcol + 1) {
      temp = B[kAcol];
      B[kAcol] = B[ipiv[kAcol] - 1];
      B[ipiv[kAcol] - 1] = temp;
    }
  }

  for (k = 0; k < 6; k++) {
    kAcol = 6 * k;
    if (B[k] != 0.0) {
      for (jy = k + 1; jy + 1 < 7; jy++) {
        B[jy] -= B[k] * b_A[jy + kAcol];
      }
    }
  }

  for (k = 5; k > -1; k += -1) {
    kAcol = 6 * k;
    if (B[k] != 0.0) {
      B[k] /= b_A[k + kAcol];
      for (jy = 0; jy + 1 <= k; jy++) {
        B[jy] -= B[k] * b_A[jy + kAcol];
      }
    }
  }
}

/*
 * File trailer for mldivide.c
 *
 * [EOF]
 */
