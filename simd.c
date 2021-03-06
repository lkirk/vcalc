#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "simde/x86/avx512.h"

int main() {
  /* Initialize the two argument vectors */
  // float a[] = {2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0};
  // simde__m256 evens =
  //     simde_mm256_set_ps(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
  // float b[] = {1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0};
  // simde__m256 odds =
  //     simde_mm256_set_ps(b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);

  // simde__m256 *c = aligned_alloc(32, 8);
  // simde__m256 *d = aligned_alloc(32, 8);
  simde_float32 *odds = aligned_alloc(32, 8);
  simde_float32 *evens = aligned_alloc(32, 8);

  size_t idx = 0;
  for (float_t i = 1; i <= 15; i += 2) {
    odds[idx] = i;
    idx++;
  }

  idx = 0;
  for (float_t i = 2; i <= 16; i += 2) {
    evens[idx] = i;
    idx++;
  }

  /* Compute the difference between the two vectors */
  simde__m256 evens_v = simde_mm256_load_ps(evens);
  simde__m256 odds_v = simde_mm256_load_ps(odds);
  simde__m256 result = simde_mm256_sub_ps(evens_v, odds_v);

  /* Display the elements of the result vector */
  float* f = (float*)&result;
  printf("%f %f %f %f %f %f %f %f\n",
    f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);
}
