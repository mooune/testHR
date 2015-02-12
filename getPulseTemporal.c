/*
 * File: getPulseTemporal.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 31-Jan-2015 18:42:34
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getPulseTemporal.h"

/* Function Declarations */
static void assignOutputs(const double y[128], const double x[128], const double
  iPk_data[], const int iPk_size[1], double YpkOut_data[], int YpkOut_size[2],
  double XpkOut_data[], int XpkOut_size[2]);
static void b_diff(const double x_data[], const int x_size[2], double y_data[],
                   int y_size[2]);
static void b_eml_li_find(const boolean_T x_data[], const int x_size[2], int
  y_data[], int y_size[2]);
static void b_eml_sort(const double x_data[], const int x_size[1], int dim,
  double y_data[], int y_size[1], int idx_data[], int idx_size[1]);
static void b_eml_sort_idx(const double x_data[], const int x_size[1], int
  idx_data[], int idx_size[1]);
static void b_sign(double x_data[], int x_size[1]);
static void c_eml_sort(const double x_data[], const int x_size[1], double
  y_data[], int y_size[1]);
static void c_findPeaksSeparatedByMoreThanM(const double y[128], const double
  iPk_data[], const int iPk_size[1], double idx_data[], int idx_size[1]);
static void diff(const double x_data[], const int x_size[1], double y_data[],
                 int y_size[1]);
static void do_vectors(const double a_data[], const int a_size[1], const double
  b_data[], const int b_size[1], double c_data[], int c_size[1], int ia_data[],
  int ia_size[1], int ib_data[], int ib_size[1]);
static void eml_li_find(const boolean_T x_data[], const int x_size[1], int
  y_data[], int y_size[1]);
static int eml_nonsingleton_dim(const int x_size[1]);
static void eml_sort(const double x_data[], const int x_size[1], double y_data[],
                     int y_size[1], int idx_data[], int idx_size[1]);
static void eml_sort_idx(const double x_data[], const int x_size[1], int
  idx_data[], int idx_size[1]);
static void findLocalMaxima(const double yTemp[128], double iPk_data[], int
  iPk_size[1], double iInflect_data[], int iInflect_size[1]);
static void findpeaks(const double Yin[128], double Ypk_data[], int Ypk_size[2],
                      double Xpk_data[], int Xpk_size[2]);
static void getAllPeaks(const double y[128], double iPk_data[], int iPk_size[1],
  double iInf_data[], int iInf_size[1], double iInflect_data[], int
  iInflect_size[1]);
static double mean(const double x_data[], const int x_size[2]);
static void removePeaksBelowThreshold(const double Y[128], double iPk_data[],
  int iPk_size[1]);
static double rt_roundd_snf(double u);
static double skip_to_last_equal_value(int *k, const double x_data[], const int
  x_size[1]);
static double var(const double x_data[], const int x_size[2]);

/* Function Definitions */

/*
 * Arguments    : const double y[128]
 *                const double x[128]
 *                const double iPk_data[]
 *                const int iPk_size[1]
 *                double YpkOut_data[]
 *                int YpkOut_size[2]
 *                double XpkOut_data[]
 *                int XpkOut_size[2]
 * Return Type  : void
 */
static void assignOutputs(const double y[128], const double x[128], const double
  iPk_data[], const int iPk_size[1], double YpkOut_data[], int YpkOut_size[2],
  double XpkOut_data[], int XpkOut_size[2])
{
  int loop_ub;
  int i4;
  YpkOut_size[0] = 1;
  YpkOut_size[1] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i4 = 0; i4 < loop_ub; i4++) {
    YpkOut_data[i4] = y[(int)iPk_data[i4] - 1];
  }

  XpkOut_size[0] = 1;
  XpkOut_size[1] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i4 = 0; i4 < loop_ub; i4++) {
    XpkOut_data[i4] = x[(int)iPk_data[i4] - 1];
  }
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 *                double y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
static void b_diff(const double x_data[], const int x_size[2], double y_data[],
                   int y_size[2])
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
 * Arguments    : const boolean_T x_data[]
 *                const int x_size[2]
 *                int y_data[]
 *                int y_size[2]
 * Return Type  : void
 */
static void b_eml_li_find(const boolean_T x_data[], const int x_size[2], int
  y_data[], int y_size[2])
{
  int n;
  int k;
  int i;
  n = x_size[1];
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x_data[i - 1]) {
      k++;
    }
  }

  y_size[0] = 1;
  y_size[1] = k;
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x_data[i - 1]) {
      y_data[k] = i;
      k++;
    }
  }
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                int dim
 *                double y_data[]
 *                int y_size[1]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
static void b_eml_sort(const double x_data[], const int x_size[1], int dim,
  double y_data[], int y_size[1], int idx_data[], int idx_size[1])
{
  int vlen;
  double vwork_data[256];
  int vwork_size[1];
  int vstride;
  int k;
  int i1;
  int j;
  int ix;
  int iidx_size[1];
  int iidx_data[256];
  if (dim <= 1) {
    vlen = x_size[0];
  } else {
    vlen = 1;
  }

  vwork_size[0] = (short)vlen;
  y_size[0] = x_size[0];
  idx_size[0] = (short)x_size[0];
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= x_size[0];
    k = 2;
  }

  i1 = -1;
  for (j = 1; j <= vstride; j++) {
    i1++;
    ix = i1;
    for (k = 0; k < vlen; k++) {
      vwork_data[k] = x_data[ix];
      ix += vstride;
    }

    eml_sort_idx(vwork_data, vwork_size, iidx_data, iidx_size);
    ix = i1;
    for (k = 0; k < vlen; k++) {
      y_data[ix] = vwork_data[iidx_data[k] - 1];
      idx_data[ix] = iidx_data[k];
      ix += vstride;
    }
  }
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
static void b_eml_sort_idx(const double x_data[], const int x_size[1], int
  idx_data[], int idx_size[1])
{
  int n;
  int k;
  boolean_T p;
  int i;
  int idx0_data[256];
  int i2;
  int j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  n = x_size[0];
  idx_size[0] = (short)x_size[0];
  if (x_size[0] == 0) {
    for (k = 1; k <= n; k++) {
      idx_data[k - 1] = k;
    }
  } else {
    for (k = 1; k <= n; k++) {
      idx_data[k - 1] = k;
    }

    for (k = 1; k <= n - 1; k += 2) {
      if ((x_data[k - 1] <= x_data[k]) || rtIsNaN(x_data[k])) {
        p = true;
      } else {
        p = false;
      }

      if (p) {
      } else {
        idx_data[k - 1] = k + 1;
        idx_data[k] = k;
      }
    }

    k = x_size[0];
    for (i = 0; i < k; i++) {
      idx0_data[i] = 1;
    }

    i = 2;
    while (i < n) {
      i2 = i << 1;
      j = 1;
      for (pEnd = 1 + i; pEnd < n + 1; pEnd = qEnd + i) {
        b_p = j;
        q = pEnd - 1;
        qEnd = j + i2;
        if (qEnd > n + 1) {
          qEnd = n + 1;
        }

        k = 0;
        kEnd = qEnd - j;
        while (k + 1 <= kEnd) {
          if ((x_data[idx_data[b_p - 1] - 1] <= x_data[idx_data[q] - 1]) ||
              rtIsNaN(x_data[idx_data[q] - 1])) {
            p = true;
          } else {
            p = false;
          }

          if (p) {
            idx0_data[k] = idx_data[b_p - 1];
            b_p++;
            if (b_p == pEnd) {
              while (q + 1 < qEnd) {
                k++;
                idx0_data[k] = idx_data[q];
                q++;
              }
            }
          } else {
            idx0_data[k] = idx_data[q];
            q++;
            if (q + 1 == qEnd) {
              while (b_p < pEnd) {
                k++;
                idx0_data[k] = idx_data[b_p - 1];
                b_p++;
              }
            }
          }

          k++;
        }

        for (k = 0; k + 1 <= kEnd; k++) {
          idx_data[(j + k) - 1] = idx0_data[k];
        }

        j = qEnd;
      }

      i = i2;
    }
  }
}

/*
 * Arguments    : double x_data[]
 *                int x_size[1]
 * Return Type  : void
 */
static void b_sign(double x_data[], int x_size[1])
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
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                double y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
static void c_eml_sort(const double x_data[], const int x_size[1], double
  y_data[], int y_size[1])
{
  int dim;
  int vlen;
  double vwork_data[256];
  int vwork_size[1];
  int vstride;
  int k;
  int j;
  int ix;
  int iidx_size[1];
  int iidx_data[256];
  dim = eml_nonsingleton_dim(x_size);
  if (dim <= 1) {
    vlen = x_size[0];
  } else {
    vlen = 1;
  }

  vwork_size[0] = (short)vlen;
  y_size[0] = x_size[0];
  vstride = 1;
  k = 1;
  while (k <= dim - 1) {
    vstride *= x_size[0];
    k = 2;
  }

  dim = -1;
  for (j = 1; j <= vstride; j++) {
    dim++;
    ix = dim;
    for (k = 0; k < vlen; k++) {
      vwork_data[k] = x_data[ix];
      ix += vstride;
    }

    b_eml_sort_idx(vwork_data, vwork_size, iidx_data, iidx_size);
    ix = dim;
    for (k = 0; k < vlen; k++) {
      y_data[ix] = vwork_data[iidx_data[k] - 1];
      ix += vstride;
    }
  }
}

/*
 * Arguments    : const double y[128]
 *                const double iPk_data[]
 *                const int iPk_size[1]
 *                double idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
static void c_findPeaksSeparatedByMoreThanM(const double y[128], const double
  iPk_data[], const int iPk_size[1], double idx_data[], int idx_size[1])
{
  double y_data[1];
  signed char y_size[2];
  int i3;
  static const signed char iv0[2] = { 1, 0 };

  int loop_ub;
  double locs_data[256];
  double b_y_data[256];
  int b_y_size[1];
  int iidx_size[1];
  int iidx_data[256];
  int locs_temp_size[1];
  double locs_temp_data[256];
  int sortIdx_size_idx_0;
  int sortIdx_data[256];
  boolean_T idelete_data[256];
  int i;
  boolean_T b_idelete_data[256];
  int idelete_size[1];
  if (iPk_size[0] == 0) {
    for (i3 = 0; i3 < 2; i3++) {
      y_size[i3] = iv0[i3];
    }

    idx_size[0] = y_size[1];
    loop_ub = y_size[1];
    i3 = 0;
    while (i3 <= loop_ub - 1) {
      idx_data[0] = y_data[0];
      i3 = 1;
    }
  } else {
    loop_ub = iPk_size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      locs_data[i3] = 1.0 + (double)((int)iPk_data[i3] - 1);
    }

    b_y_size[0] = iPk_size[0];
    loop_ub = iPk_size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      b_y_data[i3] = y[(int)iPk_data[i3] - 1];
    }

    eml_sort(b_y_data, b_y_size, locs_temp_data, locs_temp_size, iidx_data,
             iidx_size);
    sortIdx_size_idx_0 = iidx_size[0];
    loop_ub = iidx_size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      sortIdx_data[i3] = iidx_data[i3];
    }

    loop_ub = iidx_size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      locs_temp_data[i3] = locs_data[sortIdx_data[i3] - 1];
    }

    loop_ub = (short)iidx_size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      idelete_data[i3] = false;
    }

    for (i = 0; i < sortIdx_size_idx_0; i++) {
      if (!idelete_data[i]) {
        loop_ub = (short)sortIdx_size_idx_0;
        for (i3 = 0; i3 < loop_ub; i3++) {
          idelete_data[i3] = (idelete_data[i3] || ((locs_temp_data[i3] >=
            locs_data[sortIdx_data[i] - 1] - 8.0) && (locs_temp_data[i3] <=
            locs_data[sortIdx_data[i] - 1] + 8.0)));
        }

        idelete_data[i] = false;
      }
    }

    idelete_size[0] = (short)iidx_size[0];
    loop_ub = (short)iidx_size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      b_idelete_data[i3] = !idelete_data[i3];
    }

    eml_li_find(b_idelete_data, idelete_size, iidx_data, iidx_size);
    locs_temp_size[0] = iidx_size[0];
    loop_ub = iidx_size[0];
    for (i3 = 0; i3 < loop_ub; i3++) {
      locs_temp_data[i3] = sortIdx_data[iidx_data[i3] - 1];
    }

    c_eml_sort(locs_temp_data, locs_temp_size, idx_data, idx_size);
  }
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                double y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
static void diff(const double x_data[], const int x_size[1], double y_data[],
                 int y_size[1])
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
static void do_vectors(const double a_data[], const int a_size[1], const double
  b_data[], const int b_size[1], double c_data[], int c_size[1], int ia_data[],
  int ia_size[1], int ib_data[], int ib_size[1])
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
 * Arguments    : const boolean_T x_data[]
 *                const int x_size[1]
 *                int y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
static void eml_li_find(const boolean_T x_data[], const int x_size[1], int
  y_data[], int y_size[1])
{
  int n;
  int k;
  int i;
  n = x_size[0];
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x_data[i - 1]) {
      k++;
    }
  }

  y_size[0] = k;
  k = 0;
  for (i = 1; i <= n; i++) {
    if (x_data[i - 1]) {
      y_data[k] = i;
      k++;
    }
  }
}

/*
 * Arguments    : const int x_size[1]
 * Return Type  : int
 */
static int eml_nonsingleton_dim(const int x_size[1])
{
  int dim;
  dim = 2;
  if (x_size[0] != 1) {
    dim = 1;
  }

  return dim;
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                double y_data[]
 *                int y_size[1]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
static void eml_sort(const double x_data[], const int x_size[1], double y_data[],
                     int y_size[1], int idx_data[], int idx_size[1])
{
  int dim;
  dim = 2;
  if (x_size[0] != 1) {
    dim = 1;
  }

  b_eml_sort(x_data, x_size, dim, y_data, y_size, idx_data, idx_size);
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
static void eml_sort_idx(const double x_data[], const int x_size[1], int
  idx_data[], int idx_size[1])
{
  int n;
  int k;
  boolean_T p;
  int i;
  int idx0_data[256];
  int i2;
  int j;
  int pEnd;
  int b_p;
  int q;
  int qEnd;
  int kEnd;
  n = x_size[0];
  idx_size[0] = (short)x_size[0];
  for (k = 1; k <= n; k++) {
    idx_data[k - 1] = k;
  }

  for (k = 1; k <= n - 1; k += 2) {
    if ((x_data[k - 1] >= x_data[k]) || rtIsNaN(x_data[k - 1])) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
    } else {
      idx_data[k - 1] = k + 1;
      idx_data[k] = k;
    }
  }

  k = x_size[0];
  for (i = 0; i < k; i++) {
    idx0_data[i] = 1;
  }

  i = 2;
  while (i < n) {
    i2 = i << 1;
    j = 1;
    for (pEnd = 1 + i; pEnd < n + 1; pEnd = qEnd + i) {
      b_p = j - 1;
      q = pEnd;
      qEnd = j + i2;
      if (qEnd > n + 1) {
        qEnd = n + 1;
      }

      k = 0;
      kEnd = qEnd - j;
      while (k + 1 <= kEnd) {
        if ((x_data[idx_data[b_p] - 1] >= x_data[idx_data[q - 1] - 1]) ||
            rtIsNaN(x_data[idx_data[b_p] - 1])) {
          p = true;
        } else {
          p = false;
        }

        if (p) {
          idx0_data[k] = idx_data[b_p];
          b_p++;
          if (b_p + 1 == pEnd) {
            while (q < qEnd) {
              k++;
              idx0_data[k] = idx_data[q - 1];
              q++;
            }
          }
        } else {
          idx0_data[k] = idx_data[q - 1];
          q++;
          if (q == qEnd) {
            while (b_p + 1 < pEnd) {
              k++;
              idx0_data[k] = idx_data[b_p];
              b_p++;
            }
          }
        }

        k++;
      }

      for (k = 0; k + 1 <= kEnd; k++) {
        idx_data[(j + k) - 1] = idx0_data[k];
      }

      j = qEnd;
    }

    i = i2;
  }
}

/*
 * Arguments    : const double yTemp[128]
 *                double iPk_data[]
 *                int iPk_size[1]
 *                double iInflect_data[]
 *                int iInflect_size[1]
 * Return Type  : void
 */
static void findLocalMaxima(const double yTemp[128], double iPk_data[], int
  iPk_size[1], double iInflect_data[], int iInflect_size[1])
{
  double b_yTemp[130];
  boolean_T yFinite[130];
  int i;
  boolean_T x[129];
  int idx;
  unsigned char ii_data[129];
  int ii;
  boolean_T exitg3;
  boolean_T guard3 = false;
  int loop_ub;
  unsigned char tmp_data[130];
  int i2;
  unsigned char iTemp_data[130];
  double yTemp_data[130];
  int yTemp_size[1];
  int s_size[1];
  double s_data[129];
  double b_tmp_data[129];
  boolean_T x_data[128];
  int b_ii_data[128];
  int ii_size_idx_0;
  boolean_T exitg2;
  boolean_T guard2 = false;
  int c_ii_data[128];
  boolean_T exitg1;
  boolean_T guard1 = false;
  b_yTemp[0] = rtNaN;
  memcpy(&b_yTemp[1], &yTemp[0], sizeof(double) << 7);
  b_yTemp[129] = rtNaN;
  for (i = 0; i < 130; i++) {
    yFinite[i] = !rtIsNaN(b_yTemp[i]);
  }

  for (i = 0; i < 129; i++) {
    x[i] = ((b_yTemp[i] != b_yTemp[i + 1]) && (yFinite[i] || yFinite[i + 1]));
  }

  idx = 0;
  ii = 1;
  exitg3 = false;
  while ((!exitg3) && (ii < 130)) {
    guard3 = false;
    if (x[ii - 1]) {
      idx++;
      ii_data[idx - 1] = (unsigned char)ii;
      if (idx >= 129) {
        exitg3 = true;
      } else {
        guard3 = true;
      }
    } else {
      guard3 = true;
    }

    if (guard3) {
      ii++;
    }
  }

  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }

  tmp_data[0] = 1;
  for (ii = 0; ii < loop_ub; ii++) {
    tmp_data[ii + 1] = (unsigned char)(ii_data[ii] + 1);
  }

  if (1 > idx) {
    i2 = 0;
  } else {
    i2 = idx;
  }

  i = 1 + i2;
  for (ii = 0; ii < i; ii++) {
    iTemp_data[ii] = tmp_data[ii];
  }

  yTemp_size[0] = 1 + loop_ub;
  loop_ub++;
  for (ii = 0; ii < loop_ub; ii++) {
    yTemp_data[ii] = b_yTemp[iTemp_data[ii] - 1];
  }

  diff(yTemp_data, yTemp_size, s_data, s_size);
  b_sign(s_data, s_size);
  diff(s_data, s_size, b_tmp_data, yTemp_size);
  loop_ub = yTemp_size[0];
  for (ii = 0; ii < loop_ub; ii++) {
    x_data[ii] = (b_tmp_data[ii] < 0.0);
  }

  i = yTemp_size[0];
  idx = 0;
  ii_size_idx_0 = yTemp_size[0];
  ii = 1;
  exitg2 = false;
  while ((!exitg2) && (ii <= i)) {
    guard2 = false;
    if (x_data[ii - 1]) {
      idx++;
      b_ii_data[idx - 1] = ii;
      if (idx >= i) {
        exitg2 = true;
      } else {
        guard2 = true;
      }
    } else {
      guard2 = true;
    }

    if (guard2) {
      ii++;
    }
  }

  if (yTemp_size[0] == 1) {
    if (idx == 0) {
      ii_size_idx_0 = 0;
    }
  } else if (1 > idx) {
    ii_size_idx_0 = 0;
  } else {
    ii_size_idx_0 = idx;
  }

  if (1 > s_size[0] - 1) {
    loop_ub = -1;
  } else {
    loop_ub = s_size[0] - 2;
  }

  if (2 > s_size[0]) {
    ii = 0;
  } else {
    ii = 1;
  }

  for (i = 0; i <= loop_ub; i++) {
    x_data[i] = (s_data[i] != s_data[ii + i]);
  }

  idx = 0;
  i = loop_ub + 1;
  ii = 1;
  exitg1 = false;
  while ((!exitg1) && (ii <= loop_ub + 1)) {
    guard1 = false;
    if (x_data[ii - 1]) {
      idx++;
      c_ii_data[idx - 1] = ii;
      if (idx >= loop_ub + 1) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ii++;
    }
  }

  if (loop_ub + 1 == 1) {
    if (idx == 0) {
      i = 0;
    }
  } else if (1 > idx) {
    i = 0;
  } else {
    i = idx;
  }

  iInflect_size[0] = i;
  for (ii = 0; ii < i; ii++) {
    iInflect_data[ii] = (double)iTemp_data[c_ii_data[ii]] - 1.0;
  }

  iPk_size[0] = ii_size_idx_0;
  for (ii = 0; ii < ii_size_idx_0; ii++) {
    iPk_data[ii] = (double)iTemp_data[b_ii_data[ii]] - 1.0;
  }
}

/*
 * Arguments    : const double Yin[128]
 *                double Ypk_data[]
 *                int Ypk_size[2]
 *                double Xpk_data[]
 *                int Xpk_size[2]
 * Return Type  : void
 */
static void findpeaks(const double Yin[128], double Ypk_data[], int Ypk_size[2],
                      double Xpk_data[], int Xpk_size[2])
{
  int iInflect_size[1];
  double iInflect_data[128];
  int iInfite_size[1];
  double iInfite_data[128];
  int iFinite_size[1];
  double iFinite_data[128];
  int loop_ub;
  int i1;
  boolean_T Yin_data[128];
  int Yin_size[1];
  int tmp_data[256];
  int iPk_size[1];
  double iPk_data[256];
  int ib_data[128];
  int ia_data[128];
  double b_iPk_data[256];
  double c_iPk_data[256];
  double d_iPk_data[256];
  int b_iPk_size[1];
  getAllPeaks(Yin, iFinite_data, iFinite_size, iInfite_data, iInfite_size,
              iInflect_data, iInflect_size);
  iInflect_size[0] = iFinite_size[0];
  loop_ub = iFinite_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    iInflect_data[i1] = iFinite_data[i1];
  }

  if (!(iFinite_size[0] == 0)) {
    Yin_size[0] = iFinite_size[0];
    loop_ub = iFinite_size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      Yin_data[i1] = (Yin[(int)iFinite_data[i1] - 1] > rtMinusInf);
    }

    eml_li_find(Yin_data, Yin_size, tmp_data, iFinite_size);
    iInflect_size[0] = iFinite_size[0];
    loop_ub = iFinite_size[0];
    for (i1 = 0; i1 < loop_ub; i1++) {
      iInflect_data[i1] = iFinite_data[tmp_data[i1] - 1];
    }
  }

  removePeaksBelowThreshold(Yin, iInflect_data, iInflect_size);
  iPk_size[0] = iInflect_size[0];
  loop_ub = iInflect_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    iPk_data[i1] = iInflect_data[i1];
  }

  do_vectors(iPk_data, iPk_size, iInfite_data, iInfite_size, b_iPk_data,
             iFinite_size, ia_data, iInflect_size, ib_data, Yin_size);
  c_findPeaksSeparatedByMoreThanM(Yin, b_iPk_data, iFinite_size, iPk_data,
    iPk_size);
  if (iPk_size[0] > 128) {
    memcpy(&c_iPk_data[0], &iPk_data[0], sizeof(double) << 7);
    iPk_size[0] = 128;
    for (i1 = 0; i1 < 128; i1++) {
      iPk_data[i1] = c_iPk_data[i1];
    }
  }

  for (i1 = 0; i1 < 128; i1++) {
    iFinite_data[i1] = 1.0 + (double)i1;
  }

  b_iPk_size[0] = iPk_size[0];
  loop_ub = iPk_size[0];
  for (i1 = 0; i1 < loop_ub; i1++) {
    d_iPk_data[i1] = b_iPk_data[(int)iPk_data[i1] - 1];
  }

  assignOutputs(Yin, iFinite_data, d_iPk_data, b_iPk_size, Ypk_data, Ypk_size,
                Xpk_data, Xpk_size);
}

/*
 * Arguments    : const double y[128]
 *                double iPk_data[]
 *                int iPk_size[1]
 *                double iInf_data[]
 *                int iInf_size[1]
 *                double iInflect_data[]
 *                int iInflect_size[1]
 * Return Type  : void
 */
static void getAllPeaks(const double y[128], double iPk_data[], int iPk_size[1],
  double iInf_data[], int iInf_size[1], double iInflect_data[], int
  iInflect_size[1])
{
  boolean_T x[128];
  int i;
  unsigned char ii_data[128];
  int ii;
  boolean_T exitg1;
  boolean_T guard1 = false;
  double yTemp[128];
  for (i = 0; i < 128; i++) {
    x[i] = (rtIsInf(y[i]) && (y[i] > 0.0));
  }

  i = 0;
  ii = 1;
  exitg1 = false;
  while ((!exitg1) && (ii < 129)) {
    guard1 = false;
    if (x[ii - 1]) {
      i++;
      ii_data[i - 1] = (unsigned char)ii;
      if (i >= 128) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ii++;
    }
  }

  if (1 > i) {
    i = 0;
  }

  iInf_size[0] = i;
  for (ii = 0; ii < i; ii++) {
    iInf_data[ii] = ii_data[ii];
  }

  memcpy(&yTemp[0], &y[0], sizeof(double) << 7);
  for (ii = 0; ii < i; ii++) {
    ii_data[ii] = (unsigned char)iInf_data[ii];
  }

  for (ii = 0; ii < i; ii++) {
    yTemp[ii_data[ii] - 1] = rtNaN;
  }

  findLocalMaxima(yTemp, iPk_data, iPk_size, iInflect_data, iInflect_size);
}

/*
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 * Return Type  : double
 */
static double mean(const double x_data[], const int x_size[2])
{
  double y;
  int k;
  if (x_size[1] == 0) {
    y = 0.0;
  } else {
    y = x_data[0];
    for (k = 2; k <= x_size[1]; k++) {
      y += x_data[k - 1];
    }
  }

  y /= (double)x_size[1];
  return y;
}

/*
 * Arguments    : const double Y[128]
 *                double iPk_data[]
 *                int iPk_size[1]
 * Return Type  : void
 */
static void removePeaksBelowThreshold(const double Y[128], double iPk_data[],
  int iPk_size[1])
{
  unsigned char unnamed_idx_0;
  double base_data[128];
  int k;
  boolean_T Y_data[128];
  int Y_size[1];
  int i6;
  int tmp_size[1];
  int tmp_data[256];
  unnamed_idx_0 = (unsigned char)iPk_size[0];
  for (k = 0; k + 1 <= unnamed_idx_0; k++) {
    if ((Y[(int)(iPk_data[k] - 1.0) - 1] >= Y[(int)(iPk_data[k] + 1.0) - 1]) ||
        rtIsNaN(Y[(int)(iPk_data[k] + 1.0) - 1])) {
      base_data[k] = Y[(int)(iPk_data[k] - 1.0) - 1];
    } else {
      base_data[k] = Y[(int)(iPk_data[k] + 1.0) - 1];
    }
  }

  Y_size[0] = iPk_size[0];
  k = iPk_size[0];
  for (i6 = 0; i6 < k; i6++) {
    Y_data[i6] = (Y[(int)iPk_data[i6] - 1] - base_data[i6] >= 0.0);
  }

  eml_li_find(Y_data, Y_size, tmp_data, tmp_size);
  k = tmp_size[0];
  for (i6 = 0; i6 < k; i6++) {
    base_data[i6] = iPk_data[tmp_data[i6] - 1];
  }

  iPk_size[0] = tmp_size[0];
  k = tmp_size[0];
  for (i6 = 0; i6 < k; i6++) {
    iPk_data[i6] = base_data[i6];
  }
}

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

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
 * Arguments    : const double x_data[]
 *                const int x_size[2]
 * Return Type  : double
 */
static double var(const double x_data[], const int x_size[2])
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
 * This function tries to compute a pulse given a windowed signal
 * Arguments    : const double channelOfInterest[128]
 *                double frameRate
 * Return Type  : unsigned char
 */
unsigned char getPulseTemporal(const double channelOfInterest[128], double
  frameRate)
{
  unsigned char bestPulse;
  int locs_size[2];
  double locs_data[256];
  int locsSelelected_size[2];
  double locsSelelected_data[256];
  boolean_T b_locsSelelected_data[256];
  int b_locsSelelected_size[2];
  int loop_ub;
  int i0;
  int tmp_data[256];
  int pksSelected_size[2];
  double pksSelected_data[256];
  int c_locsSelelected_size[2];
  boolean_T quality;
  double b_bestPulse;
  double b_tmp_data[255];
  double varianceLocsPulse;
  int b_pksSelected_size[2];
  findpeaks(channelOfInterest, locsSelelected_data, locsSelelected_size,
            locs_data, locs_size);

  /* %  ,'MINPEAKHEIGHT',minpeakheight); */
  b_locsSelelected_size[0] = 1;
  b_locsSelelected_size[1] = locsSelelected_size[1];
  loop_ub = locsSelelected_size[0] * locsSelelected_size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_locsSelelected_data[i0] = (locsSelelected_data[i0] > 0.0);
  }

  b_eml_li_find(b_locsSelelected_data, b_locsSelelected_size, tmp_data,
                locs_size);
  pksSelected_size[0] = 1;
  pksSelected_size[1] = locs_size[1];
  loop_ub = locs_size[0] * locs_size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    pksSelected_data[i0] = locsSelelected_data[tmp_data[i0] - 1];
  }

  c_locsSelelected_size[0] = 1;
  c_locsSelelected_size[1] = locsSelelected_size[1];
  loop_ub = locsSelelected_size[0] * locsSelelected_size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_locsSelelected_data[i0] = (locsSelelected_data[i0] > 0.0);
  }

  b_eml_li_find(b_locsSelelected_data, c_locsSelelected_size, tmp_data,
                locs_size);
  locsSelelected_size[0] = 1;
  locsSelelected_size[1] = locs_size[1];
  loop_ub = locs_size[0] * locs_size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    locsSelelected_data[i0] = locs_data[tmp_data[i0] - 1];
  }

  /*  some maths : */
  /*  let state that a human heart rate is between 30 and 220 pulse per minutes */
  /*  this give a frequency between 0.5 and 3.66 hz,  */
  /*  and a period between 0.27 and 2s  */
  /*  */
  /*  the sample time is set to 30 images per seconds in the Xcode project, due */
  /*  to iphone 5 camera limits. */
  /*  therefore the duration between 2 samples is 0.033 */
  /*  */
  /*  if we want to catch a rate of 220, the minpeakdistance must be less than */
  /*  8.2, so i take 8. */
  /*  setting it to 9 increase algorithm quality but limits the max freq to 200 */
  /* % Evaluating Quality */
  /*  number of peaks if we consider a frame rate of 30 image per seconds, and */
  /*  a bpm from 30 bpm to 220bpm , we should see, in a 128 elements frame */
  /*  (4.2667 seconds) from 2 to 8 peaks  */
  /*   */
  quality = true;
  b_bestPulse = 0.0;
  if (!(locs_size[1] == 0)) {
    if (locs_size[1] > 10) {
      quality = false;
    }

    b_diff(locsSelelected_data, locsSelelected_size, b_tmp_data, locs_size);
    varianceLocsPulse = var(b_tmp_data, locs_size);
    if (varianceLocsPulse > 5.0) {
      quality = false;
    }

    varianceLocsPulse = mean(pksSelected_data, pksSelected_size);
    b_pksSelected_size[0] = 1;
    b_pksSelected_size[1] = pksSelected_size[1];
    loop_ub = pksSelected_size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      locs_data[i0] = pksSelected_data[i0] - varianceLocsPulse;
    }

    if (var(locs_data, b_pksSelected_size) > 5.0) {
      quality = false;
    }

    if (quality) {
      b_diff(locsSelelected_data, locsSelelected_size, b_tmp_data, locs_size);
      varianceLocsPulse = mean(b_tmp_data, locs_size);
      b_bestPulse = 60.0 / (varianceLocsPulse / frameRate);
    }
  }

  /*  */
  varianceLocsPulse = rt_roundd_snf(b_bestPulse);
  if (varianceLocsPulse < 256.0) {
    if (varianceLocsPulse >= 0.0) {
      bestPulse = (unsigned char)varianceLocsPulse;
    } else {
      bestPulse = 0;
    }
  } else if (varianceLocsPulse >= 256.0) {
    bestPulse = MAX_uint8_T;
  } else {
    bestPulse = 0;
  }

  return bestPulse;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void getPulseTemporal_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void getPulseTemporal_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for getPulseTemporal.c
 *
 * [EOF]
 */
