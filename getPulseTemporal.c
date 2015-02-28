/*
 * File: getPulseTemporal.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Feb-2015 08:38:36
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getPulseTemporal.h"
#include "mean.h"
#include "diff.h"
#include "var.h"
#include "findpeaks.h"

/* Function Declarations */
static void b_eml_li_find(const boolean_T x_data[], const int x_size[2], int
  y_data[], int y_size[2]);
static double rt_roundd_snf(double u);

/* Function Definitions */

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
 * Arguments    : const double inputBuffer[128]
 *                double frameRate
 * Return Type  : unsigned char
 */
unsigned char getPulseTemporal(const double inputBuffer[128], double frameRate)
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

  /*  This function compute a pulse given a windowed signal */
  /* % detecting interesting peaks */
  /*  */
  findpeaks(inputBuffer, locsSelelected_data, locsSelelected_size, locs_data,
            locs_size);

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

  /* % Diplay results and plots */
  /*  scrsz = get(groot,'ScreenSize'); */
  /*  h = figure(100); */
  /*  caution : setting done on MATLAB running on Bootcamp on a MacBookPro Retina */
  /*  h.Position = [1 scrsz(4)*0.8/2 scrsz(3)/2 scrsz(4)/2]; */
  /*  plot(inputBuffer,'b'), grid on, title('Signals'), xlabel(''),ylabel('input signal'),hold on, plot(locsSelelected,pksSelected,'k^','markerfacecolor',[1 0 0]),legend('signal','Local extremum','Location','southeast'); */
  /*  hold off; */
  return bestPulse;
}

/*
 * File trailer for getPulseTemporal.c
 *
 * [EOF]
 */
