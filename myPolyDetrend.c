/*
 * File: myPolyDetrend.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:40:21
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "myPolyDetrend.h"
#include "mldivide.h"
#include "qr.h"

/* Function Definitions */

/*
 * myPolyDetrend  is an edition of MathWorks Polyfit function to prepare it
 *    for code generation .
 *    in our case, were we want to remove the polynomial trend, it is the
 *    residual that matter, so the residual is given as output
 *    Below the help of the original Polyfit function
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
  /*  Here are the changes introduced to the original polyfit function */
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

  /*  the following lines were commented because they are not usefull in */
  /*  our case */
  /*  S is a structure containing three elements: the triangular factor from a */
  /*  QR decomposition of the Vandermonde matrix, the degrees of freedom and */
  /*  the norm of the residuals. */
  /*  S.R = R; */
  /*  S.df = max(0,length(y) - (n+1)); */
  /*  S.normr = norm(r); */
  /* p = p.';          % Polynomial coefficients are row vectors by convention. */
}

/*
 * File trailer for myPolyDetrend.c
 *
 * [EOF]
 */
