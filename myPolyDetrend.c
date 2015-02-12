/*
 * File: myPolyDetrend.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 31-Jan-2015 18:43:19
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "myPolyDetrend.h"

/* Function Declarations */
static void b_eml_matlab_zlarf(int m, int n, int iv0, double tau, double C[768],
  int ic0, double work[6]);
static void eml_matlab_zlarf(int m, int n, int iv0, double tau, double C[768],
  int ic0, double work[6]);
static double eml_matlab_zlarfg(int n, double *alpha1, double x[768], int ix0);
static double eml_xnrm2(int n, const double x[768], int ix0);
static void eml_xscal(int n, double a, double x[768], int ix0);
static void mldivide(const double A[36], double B[6]);
static void qr(const double A[768], double Q[768], double R[36]);
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
 * Arguments    : const double A[36]
 *                double B[6]
 * Return Type  : void
 */
static void mldivide(const double A[36], double B[6])
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
 * Arguments    : const double A[768]
 *                double Q[768]
 *                double R[36]
 * Return Type  : void
 */
static void qr(const double A[768], double Q[768], double R[36])
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
 * myPOLYFIT is an edition of MathWorks polyfit function to prepare it
 *    for code generation .
 *    in our case, were we want to remove the polynomial trend, it is the
 *    residual that matter, so the residual is given as output
 *
 *    Fit polynomial to data.
 *    P = POLYFIT(X,Y,N) finds the coefficients of a polynomial P(X) of
 *    degree N that fits the data Y best in a least-squares sense. P is a
 *    row vector of length N+1 containing the polynomial coefficients in
 *    descending powers, P(1)*X^N + P(2)*X^(N-1) +...+ P(N)*X + P(N+1).
 *
 *    [P,S] = POLYFIT(X,Y,N) returns the polynomial coefficients P and a
 *    structure S for use with POLYVAL to obtain error estimates for
 *    predictions.  S contains fields for the triangular factor (R) from a QR
 *    decomposition of the Vandermonde matrix of X, the degrees of freedom
 *    (df), and the norm of the residuals (normr).  If the data Y are random,
 *    an estimate of the covariance matrix of P is (Rinv*Rinv')*normr^2/df,
 *    where Rinv is the inverse of R.
 *
 *    [P,S,MU] = POLYFIT(X,Y,N) finds the coefficients of a polynomial in
 *    XHAT = (X-MU(1))/MU(2) where MU(1) = MEAN(X) and MU(2) = STD(X). This
 *    centering and scaling transformation improves the numerical properties
 *    of both the polynomial and the fitting algorithm.
 *
 *    Warning messages result if N is >= length(X), if X has repeated, or
 *    nearly repeated, points, or if X might need centering and scaling.
 *
 *    Class support for inputs X,Y:
 *       float: double, single
 *
 *    See also POLY, POLYVAL, ROOTS, LSCOV.
 * Arguments    : const double y[128]
 *                double r[128]
 * Return Type  : void
 */
void myPolyDetrend(const double y[128], double r[128])
{
  double V[768];
  int i0;
  int j;
  double R[36];
  double Q[768];
  double p[6];
  double d0;

  /*    Copyright 1984-2011 The MathWorks, Inc. */
  /*  The regression problem is formulated in matrix format as: */
  /*  */
  /*     y = V*p    or */
  /*  */
  /*           3  2 */
  /*     y = [x  x  x  1] [p3 */
  /*                       p2 */
  /*                       p1 */
  /*                       p0] */
  /*  */
  /*  where the vector p contains the coefficients to be found.  For a */
  /*  7th order polynomial, matrix V would be: */
  /*  */
  /*  V = [x.^7 x.^6 x.^5 x.^4 x.^3 x.^2 x ones(size(x))]; */
  /*  Here are the changes introduced to the initial function */
  /*  to generate code even with warning function */
  /*  we only generate fit with 5 degree polynomials */
  /*  we fit on sample, so x scale is not necessary */
  memset(&V[0], 0, 768U * sizeof(double));

  /*  a problem of class definition inside the original writing */
  /*  it was necessary to initialize it that way */
  /*  Construct Vandermonde matrix. */
  for (i0 = 0; i0 < 128; i0++) {
    V[640 + i0] = 1.0;
  }

  /* edit from the Original */
  /*  V(:,n+1) = ones(length(x),1); */
  for (j = 0; j < 5; j++) {
    for (i0 = 0; i0 < 128; i0++) {
      V[i0 + ((4 - j) << 7)] = (1.0 + (double)i0) * V[i0 + ((5 - j) << 7)];
    }
  }

  /*  Solve least squares problem. */
  qr(V, Q, R);
  for (i0 = 0; i0 < 6; i0++) {
    p[i0] = 0.0;
    for (j = 0; j < 128; j++) {
      p[i0] += Q[j + (i0 << 7)] * y[j];
    }
  }

  mldivide(R, p);

  /*  Same as p = V\y; */
  for (i0 = 0; i0 < 128; i0++) {
    d0 = 0.0;
    for (j = 0; j < 6; j++) {
      d0 += V[i0 + (j << 7)] * p[j];
    }

    r[i0] = y[i0] - d0;
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void myPolyDetrend_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void myPolyDetrend_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for myPolyDetrend.c
 *
 * [EOF]
 */
