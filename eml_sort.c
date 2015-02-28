/*
 * File: eml_sort.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:38:36
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getPulseTemporal.h"
#include "eml_sort.h"

/* Function Declarations */
static void b_eml_sort(const double x_data[], const int x_size[1], int dim,
  double y_data[], int y_size[1], int idx_data[], int idx_size[1]);
static void b_eml_sort_idx(const double x_data[], const int x_size[1], int
  idx_data[], int idx_size[1]);
static int eml_nonsingleton_dim(const int x_size[1]);
static void eml_sort_idx(const double x_data[], const int x_size[1], int
  idx_data[], int idx_size[1]);

/* Function Definitions */

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
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                double y_data[]
 *                int y_size[1]
 * Return Type  : void
 */
void c_eml_sort(const double x_data[], const int x_size[1], double y_data[], int
                y_size[1])
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
 * Arguments    : const double x_data[]
 *                const int x_size[1]
 *                double y_data[]
 *                int y_size[1]
 *                int idx_data[]
 *                int idx_size[1]
 * Return Type  : void
 */
void eml_sort(const double x_data[], const int x_size[1], double y_data[], int
              y_size[1], int idx_data[], int idx_size[1])
{
  int dim;
  dim = 2;
  if (x_size[0] != 1) {
    dim = 1;
  }

  b_eml_sort(x_data, x_size, dim, y_data, y_size, idx_data, idx_size);
}

/*
 * File trailer for eml_sort.c
 *
 * [EOF]
 */
