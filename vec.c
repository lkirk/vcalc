#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_ARRAY_SIZE 10000000 // 10,000,000
#define MAX_ARRAY_DIM 256       // maximum allowed dimensions

// #define VC_ARRAY_TYPE(type) vc_vec_##type##_t
//
// #define __VC_ARRAY_TYPEDEF(type) \
//   typedef struct vc_vec_##type##_s { \
//     size_t len; \
//     size_t itemsize; \
//     size_t dims[MAX_ARRAY_DIM]; \
//     size_t ndims; \
//     type **data; \
//   } VC_ARRAY_TYPE(type)
//
// __VC_ARRAY_TYPEDEF(uint64_t);
// __VC_ARRAY_TYPEDEF(float);
// __VC_ARRAY_TYPEDEF(double);

// #define VC_ARRAY_ITER_INDICES(arr, type) {

// typedef union {
//   vc_vec_uint64_t_t u64;
//   vc_vec_float_t flt;
//   vc_vec_double_t dbl;
// } vc_array_t;

// #define __VC_ARRAY_ITER_INDICES(type) { \
//     if(strcmp(type, "u64")==0) {
//         arr = arr.u64
//     }
// uint64_t iter_indices(vc_array_t arr) {
//   arr.u64
//   return 0;
// }
// }

typedef enum dtype { UINT64, FLOAT, DOUBLE } vc_dtype_t;

typedef struct vc_vec_s {
  size_t len;
  size_t itemsize;
  size_t dims[MAX_ARRAY_DIM];
  size_t ndims;
  vc_dtype_t dtype;
  union {
    uint64_t *u64;
    float *flt;
    double *dbl;
    // complex??
  } data;
} vc_vec_t;

vc_vec_t *new_vc_vec(size_t ndims) { vc_vec_t arr = {.ndims = ndims}; }

uint64_t iter_indices(vc_array_t arr) { return 0; }

uint64_t prod(uint64_t values, ...) {
  // uint64_t result = nums[0];
  // for (int i = 1; i < 10; i++) {
  //  result *= nums[i];
  //}
  va_list args;
  va_start(args, values);
  uint64_t result = va_arg(args, uint64_t);
  printf("%lu\n", values);
  for (uint64_t i = 1; i < values; ++i) {
    printf("%lu\n", i);
    result *= va_arg(args, uint64_t);
  }
  va_end(args);
  return result;
}

  uint64_t iter_indices(vc_array_t arr) { arr.u64 return 0; }

  // #define VC_NEW_ARRAY(type, ...) \
//     __vc_array_typedef(type, ) \

  // #define call_vla(...)                                                          \
//   do {                                                                         \
//     int args[] = {__VA_ARGS__};                                                \
//     for (size_t i = 0; i < sizeof(args) / sizeof(*args); i++)                  \
//       printf("%zu\t%i\n", i, args[i]);                                         \
//   } while (0)

  // #define __ARRAY_INIT(

  int main() {
    // __vc_array_typedef(uint32_t, 2 * 3, 2, 3);
    // vc_vecuint32_t_t *a = &(vc_vecuint32_t_t){.len = 2 * 3,
    //                                           .itemsize = sizeof(uint32_t),
    //                                           .dims = {2, 3},
    //                                           .ndims = 2,
    //                                           .data = {0, 1, 2, 3, 4, 5}};
    // for (int dim = 0; dim < a->ndims; dim++) {
    //   for (int idx = 0; idx < a->dims[dim]; idx++) {
    //     printf("%d\t%d\n", dim, idx);
    //   }
    // }
    puts("========================");
    // call_vla(1, 2, 3, 4, 5, 6, 7);

    // uint64_t nums[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("result: %lu\n", prod(1, 2, 3, 4, 5, 6, 7, 8, 9, 10));
  }
