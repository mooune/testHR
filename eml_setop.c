/*
 * File: eml_setop.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:38:36
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getPulseTemporal.h"
#include "eml_setop.h"

/* Function Declarations */
static double skip_to_last_equal_value(int *k, const double x_data[], const int
  x_size[1]);

/* Function Definitions */

/*
 * Arguments    : int *k
 *                const double x_data[]
 *                const int x_size[1]
 * Return Type  : double
 */
static double skip_to_last_equal_value(int *k, const double x_data[], const int
  x_size[1])
{
  double xk;
  boolean_T exitg1;
  double absxk;
  int exponent;
  xk = x_data[*k - 1];
  exitg1 = false;
  while ((!exitg1) && (*k < x_size[0])) {
    absxk = fabs(xk / 2.0);
    if (absxk <= 2.2250738585072014E-308) {
      absxk = 4.94065645841247E-324;
    } else {
      frexp(absxk, &exponent);
      absxk = ldexp(1.0, exponent - 53);
    }

    if (fabs(xk - x_data[*k]) < absxk) {
      (*k)++;
    } else {
      exitg1 = true;
    }
  }

  return xk;
}

/*
 * Arguments    : const double a_data[]
 *                const int a_size[1]
 *                const double b_data[]
 *                const int b_size[1]
 *                double c_data[]
 *                int c_size[1]
 *                int ia_data[]
 *                int ia_size[1]
 *                int ib_data[]
 *                int ib_size[1]
 * Return Type  : void
 */
void do_vectors(const double a_data[], const int a_size[1], const double b_data[],
                const int b_size[1], double c_data[], int c_size[1], int
                ia_data[], int ia_size[1], int ib_data[], int ib_size[1])
{
  int na;
  int nb;
  int ncmax;
  int nc;
  int nia;
  int nib;
  int iafirst;
  int ialast;
  int ibfirst;
  int iblast;
  int b_ialast;
  double ak;
  int b_iblast;
  double bk;
  double absxk;
  int exponent;
  int b_ia_data[128];
  double b_c_data[256];
  na = a_size[0];
  nb = b_size[0];
  ncmax = a_size[0] + b_size[0];
  c_size[0] = (short)ncmax;
  ia_size[0] = a_size[0];
  ib_size[0] = b_size[0];
  nc = -1;
  nia = -1;
  nib = 0;
  iafirst = 1;
  ialast = 1;
  ibfirst = 0;
  iblast = 1;
  while ((ialast <= na) && (iblast <= nb)) {
    b_ialast = ialast;
    ak = skip_to_last_equal_value(&b_ialast, a_data, a_size);
    ialast = b_ialast;
    b_iblast = iblast;
    bk = skip_to_last_equal_value(&b_iblast, b_data, b_size);
    iblast = b_iblast;
    absxk = fabs(bk / 2.0);
    if (absxk <= 2.2250738585072014E-308) {
      absxk = 4.94065645841247E-324;
    } else {
      frexp(absxk, &exponent);
      absxk = ldexp(1.0, exponent - 53);
    }

    if (fabs(bk - ak) < absxk) {
      nc++;
      c_data[nc] = ak;
      nia++;
      ia_data[nia] = iafirst;
      ialast = b_ialast + 1;
      iafirst = b_ialast + 1;
      iblast = b_iblast + 1;
      ibfirst = b_iblast;
    } else if (ak < bk) {
      nc++;
      nia++;
      c_data[nc] = ak;
      ia_data[nia] = iafirst;
      ialast = b_ialast + 1;
      iafirst = b_ialast + 1;
    } else {
      nc++;
      nib++;
      c_data[nc] = bk;
      ib_data[nib - 1] = ibfirst + 1;
      iblast = b_iblast + 1;
      ibfirst = b_iblast;
    }
  }

  while (ialast <= na) {
    b_ialast = ialast;
    ak = skip_to_last_equal_value(&b_ialast, a_data, a_size);
    nc++;
    nia++;
    c_data[nc] = ak;
    ia_data[nia] = ialast;
    ialast = b_ialast + 1;
  }

  while (iblast <= nb) {
    b_iblast = iblast;
    bk = skip_to_last_equal_value(&b_iblast, b_data, b_size);
    nc++;
    nib++;
    c_data[nc] = bk;
    ib_data[nib - 1] = iblast;
    iblast = b_iblast + 1;
  }

  if (a_size[0] > 0) {
    if (1 > nia + 1) {
      na = -1;
    } else {
      na = nia;
    }

    for (nb = 0; nb <= na; nb++) {
      b_ia_data[nb] = ia_data[nb];
    }

    ia_size[0] = na + 1;
    na++;
    for (nb = 0; nb < na; nb++) {
      ia_data[nb] = b_ia_data[nb];
    }
  }

  if (b_size[0] > 0) {
    if (1 > nib) {
      na = 0;
    } else {
      na = nib;
    }

    for (nb = 0; nb < na; nb++) {
      b_ia_data[nb] = ib_data[nb];
    }

    ib_size[0] = na;
    for (nb = 0; nb < na; nb++) {
      ib_data[nb] = b_ia_data[nb];
    }
  }

  if (ncmax > 0) {
    if (1 > nc + 1) {
      na = -1;
    } else {
      na = nc;
    }

    for (nb = 0; nb <= na; nb++) {
      b_c_data[nb] = c_data[nb];
    }

    c_size[0] = na + 1;
    na++;
    for (nb = 0; nb < na; nb++) {
      c_data[nb] = b_c_data[nb];
    }
  }
}

/*
 * File trailer for eml_setop.c
 *
 * [EOF]
 */
