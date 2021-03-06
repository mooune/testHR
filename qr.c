/*
 * File: qr.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:40:21
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "myPolyDetrend.h"
#include "qr.h"

/* Function Declarations */
static void b_eml_matlab_zlarf(int m, int n, int iv0, double tau, double C[768],
  int ic0, double work[6]);
static void eml_matlab_zlarf(int m, int n, int iv0, double tau, double C[768],
  int ic0, double work[6]);
static double eml_matlab_zlarfg(int n, double *alpha1, double x[768], int ix0);
static double eml_xnrm2(int n, const double x[768], int ix0);
static void eml_xscal(int n, double a, double x[768], int ix0);
static double rt_hypotd_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                double tau
 *                double C[768]
 *                int ic0
 *                double work[6]
 * Return Type  : void
 */
static void b_eml_matlab_zlarf(int m, int n, int iv0, double tau, double C[768],
  int ic0, double work[6])
{
  int lastv;
  int i;
  int lastc;
  boolean_T exitg2;
  int ia;
  int32_T exitg1;
  int i4;
  int jy;
  int ix;
  double c;
  int j;
  if (tau != 0.0) {
    lastv = m;
    i = iv0 + m;
    while ((lastv > 0) && (C[i - 2] == 0.0)) {
      lastv--;
      i--;
    }

    lastc = n;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      i = ic0 + ((lastc - 1) << 7);
      ia = i;
      do {
        exitg1 = 0;
        if (ia <= (i + lastv) - 1) {
          if (C[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc == 0) {
    } else {
      for (i = 1; i <= lastc; i++) {
        work[i - 1] = 0.0;
      }

      i = 0;
      i4 = ic0 + ((lastc - 1) << 7);
      for (jy = ic0; jy <= i4; jy += 128) {
        ix = iv0;
        c = 0.0;
        j = (jy + lastv) - 1;
        for (ia = jy; ia <= j; ia++) {
          c += C[ia - 1] * C[ix - 1];
          ix++;
        }

        work[i] += c;
        i++;
      }
    }

    if (-tau == 0.0) {
    } else {
      i = ic0 - 1;
      jy = 0;
      for (j = 1; j <= lastc; j++) {
        if (work[jy] != 0.0) {
          c = work[jy] * -tau;
          ix = iv0;
          i4 = lastv + i;
          for (ia = i; ia + 1 <= i4; ia++) {
            C[ia] += C[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        i += 128;
      }
    }
  }
}

/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                double tau
 *                double C[768]
 *                int ic0
 *                double work[6]
 * Return Type  : void
 */
static void eml_matlab_zlarf(int m, int n, int iv0, double tau, double C[768],
  int ic0, double work[6])
{
  int lastv;
  int i;
  int lastc;
  boolean_T exitg2;
  int ia;
  int32_T exitg1;
  int i3;
  int jy;
  int ix;
  double c;
  int j;
  if (tau != 0.0) {
    lastv = m;
    i = iv0 + m;
    while ((lastv > 0) && (C[i - 2] == 0.0)) {
      lastv--;
      i--;
    }

    lastc = n;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      i = ic0 + ((lastc - 1) << 7);
      ia = i;
      do {
        exitg1 = 0;
        if (ia <= (i + lastv) - 1) {
          if (C[ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc == 0) {
    } else {
      for (i = 1; i <= lastc; i++) {
        work[i - 1] = 0.0;
      }

      i = 0;
      i3 = ic0 + ((lastc - 1) << 7);
      for (jy = ic0; jy <= i3; jy += 128) {
        ix = iv0;
        c = 0.0;
        j = (jy + lastv) - 1;
        for (ia = jy; ia <= j; ia++) {
          c += C[ia - 1] * C[ix - 1];
          ix++;
        }

        work[i] += c;
        i++;
      }
    }

    if (-tau == 0.0) {
    } else {
      i = ic0 - 1;
      jy = 0;
      for (j = 1; j <= lastc; j++) {
        if (work[jy] != 0.0) {
          c = work[jy] * -tau;
          ix = iv0;
          i3 = lastv + i;
          for (ia = i; ia + 1 <= i3; ia++) {
            C[ia] += C[ix - 1] * c;
            ix++;
          }
        }

        jy++;
        i += 128;
      }
    }
  }
}

/*
 * Arguments    : int n
 *                double *alpha1
 *                double x[768]
 *                int ix0
 * Return Type  : double
 */
static double eml_matlab_zlarfg(int n, double *alpha1, double x[768], int ix0)
{
  double tau;
  double xnorm;
  int knt;
  int i1;
  int k;
  tau = 0.0;
  if (n <= 0) {
  } else {
    xnorm = eml_xnrm2(n - 1, x, ix0);
    if (xnorm != 0.0) {
      xnorm = rt_hypotd_snf(*alpha1, xnorm);
      if (*alpha1 >= 0.0) {
        xnorm = -xnorm;
      }

      if (fabs(xnorm) < 1.0020841800044864E-292) {
        knt = 0;
        do {
          knt++;
          i1 = (ix0 + n) - 2;
          for (k = ix0; k <= i1; k++) {
            x[k - 1] *= 9.9792015476736E+291;
          }

          xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while (!(fabs(xnorm) >= 1.0020841800044864E-292));

        xnorm = rt_hypotd_snf(*alpha1, eml_xnrm2(n - 1, x, ix0));
        if (*alpha1 >= 0.0) {
          xnorm = -xnorm;
        }

        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i1 = (ix0 + n) - 2;
        for (k = ix0; k <= i1; k++) {
          x[k - 1] *= *alpha1;
        }

        for (k = 1; k <= knt; k++) {
          xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = xnorm;
      } else {
        tau = (xnorm - *alpha1) / xnorm;
        *alpha1 = 1.0 / (*alpha1 - xnorm);
        i1 = (ix0 + n) - 2;
        for (k = ix0; k <= i1; k++) {
          x[k - 1] *= *alpha1;
        }

        *alpha1 = xnorm;
      }
    }
  }

  return tau;
}

/*
 * Arguments    : int n
 *                const double x[768]
 *                int ix0
 * Return Type  : double
 */
static double eml_xnrm2(int n, const double x[768], int ix0)
{
  double y;
  double scale;
  int kend;
  int k;
  double absxk;
  double t;
  y = 0.0;
  if (n < 1) {
  } else if (n == 1) {
    y = fabs(x[ix0 - 1]);
  } else {
    scale = 2.2250738585072014E-308;
    kend = (ix0 + n) - 1;
    for (k = ix0; k <= kend; k++) {
      absxk = fabs(x[k - 1]);
      if (absxk > scale) {
        t = scale / absxk;
        y = 1.0 + y * t * t;
        scale = absxk;
      } else {
        t = absxk / scale;
        y += t * t;
      }
    }

    y = scale * sqrt(y);
  }

  return y;
}

/*
 * Arguments    : int n
 *                double a
 *                double x[768]
 *                int ix0
 * Return Type  : void
 */
static void eml_xscal(int n, double a, double x[768], int ix0)
{
  int i2;
  int k;
  i2 = (ix0 + n) - 1;
  for (k = ix0; k <= i2; k++) {
    x[k - 1] *= a;
  }
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_hypotd_snf(double u0, double u1)
{
  double y;
  double a;
  double b;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = b;
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/*
 * Arguments    : const double A[768]
 *                double Q[768]
 *                double R[36]
 * Return Type  : void
 */
void qr(const double A[768], double Q[768], double R[36])
{
  double work[6];
  int i;
  double tau[6];
  int i_i;
  double atmp;
  double b_tau;
  int itau;
  int iaii;
  memcpy(&Q[0], &A[0], 768U * sizeof(double));
  for (i = 0; i < 6; i++) {
    work[i] = 0.0;
  }

  for (i = 0; i < 6; i++) {
    i_i = i + (i << 7);
    atmp = Q[i_i];
    b_tau = eml_matlab_zlarfg(128 - i, &atmp, Q, i_i + 2);
    Q[i_i] = atmp;
    if (i + 1 < 6) {
      atmp = Q[i_i];
      Q[i_i] = 1.0;
      eml_matlab_zlarf(128 - i, 5 - i, i_i + 1, b_tau, Q, (i + ((i + 1) << 7)) +
                       1, work);
      Q[i_i] = atmp;
    }

    tau[i] = b_tau;
  }

  for (i_i = 0; i_i < 6; i_i++) {
    for (i = 0; i + 1 <= i_i + 1; i++) {
      R[i + 6 * i_i] = Q[i + (i_i << 7)];
    }

    for (i = i_i + 1; i + 1 < 7; i++) {
      R[i + 6 * i_i] = 0.0;
    }
  }

  itau = 5;
  for (i = 0; i < 6; i++) {
    work[i] = 0.0;
  }

  for (i = 5; i > -1; i += -1) {
    iaii = i + (i << 7);
    if (i + 1 < 6) {
      Q[iaii] = 1.0;
      b_eml_matlab_zlarf(128 - i, 5 - i, iaii + 1, tau[itau], Q, iaii + 129,
                         work);
    }

    eml_xscal(127 - i, -tau[itau], Q, iaii + 2);
    Q[iaii] = 1.0 - tau[itau];
    for (i_i = 1; i_i <= i; i_i++) {
      Q[iaii - i_i] = 0.0;
    }

    itau--;
  }
}

/*
 * File trailer for qr.c
 *
 * [EOF]
 */
