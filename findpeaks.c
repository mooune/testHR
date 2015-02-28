/*
 * File: findpeaks.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:38:36
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getPulseTemporal.h"
#include "findpeaks.h"
#include "eml_sort.h"
#include "eml_setop.h"
#include "diff.h"
#include "sign.h"

/* Function Declarations */
static void assignOutputs(const double y[128], const double x[128], const double
  iPk_data[], const int iPk_size[1], double YpkOut_data[], int YpkOut_size[2],
  double XpkOut_data[], int XpkOut_size[2]);
static void c_findPeaksSeparatedByMoreThanM(const double y[128], const double
  iPk_data[], const int iPk_size[1], double idx_data[], int idx_size[1]);
static void eml_li_find(const boolean_T x_data[], const int x_size[1], int
  y_data[], int y_size[1]);
static void findLocalMaxima(const double yTemp[128], double iPk_data[], int
  iPk_size[1], double iInflect_data[], int iInflect_size[1]);
static void getAllPeaks(const double y[128], double iPk_data[], int iPk_size[1],
  double iInf_data[], int iInf_size[1], double iInflect_data[], int
  iInflect_size[1]);
static void removePeaksBelowThreshold(const double Y[128], double iPk_data[],
  int iPk_size[1]);

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
 * Arguments    : const double Yin[128]
 *                double Ypk_data[]
 *                int Ypk_size[2]
 *                double Xpk_data[]
 *                int Xpk_size[2]
 * Return Type  : void
 */
void findpeaks(const double Yin[128], double Ypk_data[], int Ypk_size[2], double
               Xpk_data[], int Xpk_size[2])
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
 * File trailer for findpeaks.c
 *
 * [EOF]
 */
