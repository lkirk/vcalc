#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARRAY_SIZE 10000000 // 10,000,000
#define MAX_ARRAY_DIM 256       // maximum allowed dimensions

#define VC_ARRAY_TYPE(type) vc_vec_##type##_t
const char *__vc_type_to_format_str(char *type) {
  if (strcmp(type, "float") == 0) {
    return " %f";
  } else if (strcmp(type, "double") == 0) {
    return " %f";
  } else if (strcmp(type, "uint64_t") == 0) {
    return " %lu";
  }
  return "xxxfail"; // TODO: fail
}

#define __VC_ARRAY_TYPEDEF(type)                                               \
  typedef struct vc_vec_##type##_t {                                           \
    size_t len;                                                                \
    size_t itemsize;                                                           \
    size_t ndims;                                                              \
    size_t dims[MAX_ARRAY_DIM];                                                \
    type **data;                                                               \
  } VC_ARRAY_TYPE(type);

#define __VC_ARRAY_NEW(type)                                                   \
  VC_ARRAY_TYPE(type) * vc_vec_new_##type(size_t ndims, size_t *dims) {        \
    /* alloc array */                                                          \
    VC_ARRAY_TYPE(type) *arr = malloc(sizeof(VC_ARRAY_TYPE(type)));            \
                                                                               \
    /* compute array size (product of dims) */                                 \
    size_t len = dims[0];                                                      \
    for (size_t i = 1; i < ndims; i++) {                                       \
      if (len != 0) { /* ensures 0-len dims don't mess this up */              \
        len *= dims[i];                                                        \
      }                                                                        \
    }                                                                          \
    arr->len = len;                                                            \
    arr->ndims = ndims;                                                        \
    arr->itemsize = sizeof(type);                                              \
    for (size_t i = 0; i < ndims; i++) {                                       \
      arr->dims[i] = dims[i];                                                  \
    }                                                                          \
    arr->data = NULL;                                                          \
    return arr;                                                                \
  }

#define __VC_ARRAY_PRINT(type)                                                 \
  void vc_vec_print_##type(VC_ARRAY_TYPE(type) * arr) {                        \
    printf("array <%s> <%p>\n", #type, (void *)&arr);                          \
    puts("{");                                                                 \
    printf("  len: %lu\n", arr->len);                                          \
    printf("  itemsize: %lu\n", arr->itemsize);                                \
    printf("  ndims: %lu\n", arr->ndims);                                      \
    printf("  dims: {\n");                                                     \
    for (size_t i = 0; i < arr->ndims; i++) {                                  \
      printf("    %lu: %lu\n", i, arr->dims[i]);                               \
    }                                                                          \
    printf("  }\n");                                                           \
    printf("  data: {");                                                       \
    if (arr->data) {                                                           \
      for (size_t i = 0; i < arr->len; i++) {                                  \
        printf(__vc_type_to_format_str(#type), &(arr->data)[i]);               \
      }                                                                        \
    }                                                                          \
    printf(" }\n");                                                            \
    printf("}\n");                                                             \
  }

// // TODO: think about idx structure
// typedef struct vc_array_idx_t {
//   size_t dim;
//   size_t dim_end;
//   size_t item;
//   size_t item_end;
// } vc_array_idx_t;

//#define __VC_ARRAY_VIEW()

//#define __VC_ARRAY_INIT_ITER(type)

/*
#define __VC_ARRAY_ITER(type)                                                  \
    type vc_vec_iter##type(VC_ARRAY_TYPE(type) * arr, vc_array_idx_t * idx) { \
*/
/*
// TODO: fix logic!
#define __VC_ARRAY_ITER(type)                                                  \
  void vc_vec_iter_##type(VC_ARRAY_TYPE(type) * arr) {                         \
    size_t curr_idx = 0;                                                       \
    size_t curr_dim = 0;                                                       \
    size_t curr_lim = arr->dims[curr_dim];                                     \
    while (1) {                                                                \
      printf("curr_dim:%zu\tcurr_idx:%zu\n", curr_dim, curr_idx);              \
      if ((curr_idx + 1) == curr_lim && curr_dim + 1 == arr->ndims) {          \
        break;                                                                 \
      } else if ((curr_idx + 1) == curr_lim) {                                 \
        curr_dim++;                                                            \
        curr_idx = 0;                                                          \
        curr_lim = arr->dims[curr_dim];                                        \
      } else {                                                                 \
        curr_idx++;                                                            \
      }                                                                        \
    }                                                                          \
  }
*/

//#define __VC_ARRAY_ITER(type)                                                  \
//  void vc_vec_iter_##type(VC_ARRAY_TYPE(type) * arr) {                         \
//    size_t dims[MAX_ARRAY_DIM];                                                \
//    memccpy(dims, arr->dims, arr->ndims, arr->itemsize);                       \
//    for (size_t i = 0; i < arr->ndims; i++) {                                  \
//
//    }                                                                          \
//  }

// https://gist.github.com/kbarbary/9efb3650f1b69b2b6b18e34ad347777b

// #define __VC_ARRAY_ITER(type)                                                  \
//   void vc_vec_iter_##type(VC_ARRAY_TYPE(type) * arr) {                         \
//     size_t dim_inc = arr->ndims - 1;                                           \
//     for (size_t idx = 0; idx < arr->len; i++) {                                \
//            print (                                                             \
//     }

// #define __VC_ARRAY_CHUNK(array, axis, chunk_size)                              \
//     for (i

#define __VC_ARRAY_GEN_METHODS(type)                                           \
  __VC_ARRAY_TYPEDEF(type)                                                     \
  __VC_ARRAY_NEW(type)                                                         \
  __VC_ARRAY_PRINT(type)                                                       \
  //  __VC_ARRAY_ITER(type)

__VC_ARRAY_GEN_METHODS(uint64_t)
__VC_ARRAY_GEN_METHODS(float)
__VC_ARRAY_GEN_METHODS(double)

// static inline get_dims(dimensions, ...) {
//
// }

int main() {
  size_t ndims = 3;
  size_t dims[] = {2, 3, 3};
  vc_vec_double_t *arr = vc_vec_new_double(ndims, dims);
  double *data = calloc(arr->len, arr->itemsize);
  arr->data = &data;
  vc_vec_print_double(arr);
  // vc_vec_iter_double(arr);
}
