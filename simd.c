#include "simde/x86/avx512.h"

int main() {
  /* Initialize the two argument vectors */
  float a[] = {2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0};
  simde__m256 evens =
      simde_mm256_set_ps(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
  float b[] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0};
  simde__m256 odds =
      simde_mm256_set_ps(b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);

  /* Compute the difference between the two vectors */
  simde__m256 result = simde_mm256_sub_ps(evens, odds);

  /* Display the elements of the result vector */
  float* f = (float*)&result;
  printf("%f %f %f %f %f %f %f %f\n",
    f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);
}
