#ifndef TENSOR4_H_IMPORTED
#define TENSOR4_H_IMPORTED

#define TENSOR4_MAX_DIM 8

typedef struct {
    double* vals;
    int rank;
} tensor4;

tensor4* tensor4_zeros(int rank);

int tensor4_add(tensor4* p_tensor_a, tensor4* p_tensor_b, tensor4* p_tensor_out);

int tensor4_mult(tensor4** pp_tensors, char* indices, int num, tensor4** pp_tensor_out);

int tensor4_mult_recursive_output_indexing(int* output_indices, int recursion_depth, int output_rank, tensor4** pp_tensors, int num, tensor4** pp_tensor_out);

#endif
