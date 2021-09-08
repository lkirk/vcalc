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

typedef struct vc_array_idx_t {
  size_t loc[MAX_ARRAY_DIM];
  size_t current_dim;
  size_t current_item;
} vc_array_idx_t;

//#define __VC_ARRAY_VIEW()

//#define __VC_ARRAY_INIT_ITER(type)

#define __VC_ARRAY_ITER(type)                                                  \
  type vc_vec_iter##type(VC_ARRAY_TYPE(type) * arr, vc_array_idx_t * idx) {    \
    size_t cd = idx->current_dim


#define __VC_ARRAY_GEN_METHODS(type)                                           \
  __VC_ARRAY_TYPEDEF(type)                                                     \
  __VC_ARRAY_NEW(type)                                                         \
  __VC_ARRAY_PRINT(type)

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
}
