#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "tensor4.h"
#include "../util/string_util.h"

tensor4* tensor4_zeros(int rank) {
    tensor4* p_tensor_out = malloc(sizeof(tensor4));

    int num_entries = (int) pow(4.0, (double) rank);
    double* entries = calloc(num_entries, sizeof(double));

    p_tensor_out->rank = rank;
    p_tensor_out->vals = entries;
    return p_tensor_out;
}


int tensor4_add(tensor4* p_tensor_a, tensor4* p_tensor_b, tensor4* p_tensor_out) {
    if (p_tensor_a->rank != p_tensor_b->rank) {
        fprintf(stderr, "tensor4_add recieved tensors of different ranks\n");
        return 1;
    }

    double num_entries = pow(4.0, (double) p_tensor_a->rank);

    double entries[(int) pow(4.0, num_entries)];
    
    for (int i = 0; i < num_entries; i++) {
        entries[i] = p_tensor_a->vals[i] + p_tensor_b->vals[i];
    }

    p_tensor_out->vals = entries;
    p_tensor_out->rank = p_tensor_a->rank;
    return 0;
}


int tensor4_mult(tensor4** pp_tensors, char* indices, int num, tensor4** pp_tensor_out) {
    remove_spaces(indices);
    
    int second_occurrence = 1,
        num_double_occurrences = 0;

    int** double_occurrences;

    while (indices[second_occurrence] != '\0') {
        for (int first_occurrence = 0; first_occurrence < second_occurrence; first_occurrence++) {
            if (indices[first_occurrence] == indices[second_occurrence]) {
                double_occurrences = realloc(double_occurrences, (num_double_occurrences+1)*sizeof(int*));
                
                int occurrences[2] = {first_occurrence, second_occurrence};
                double_occurrences[num_double_occurrences] = occurrences;

                num_double_occurrences++;
            }
        }
        second_occurrence++;
    }

    int total_rank = 0;
    for (int i = 0; i < num; i++) {
        total_rank += pp_tensors[i]->rank;
    }

    int output_rank = total_rank - 2*num_double_occurrences;

    *pp_tensor_out = tensor4_zeros(output_rank);

    int* output_indices = malloc(output_rank * sizeof(int));

    tensor4_mult_recursive_output_indexing(output_indices, 0, pp_tensors, num, double_occurrences, pp_tensor_out);
    return 0;
}


int tensor4_mult_recursive_output_indexing(int* output_indices, int recursion_depth, tensor4** pp_tensors, int num, int** double_occurrences, int num_double_occurrences, tensor4** pp_tensor_out) {
    if (recursion_depth == (*pp_tensor_out)->rank) {
        recursion_depth = 0;
        int* sum_indices = malloc(num_double_occurrences * sizeof(int));
        tensor4_mult_recursive_sum_indexing(output_indices, sum_indices, recursion_depth, pp_tensors, num, double_occurrences, num_double_occurrences, pp_tensor_out);
    } else {
        for (int i = 0; i < 4; i++) {
            output_indices[recursion_depth] = i;
            recursion_depth++;
            tensor4_mult_recursive_output_indexing(output_indices, recursion_depth, pp_tensors, num, double_occurrences, num_double_occurrences, pp_tensor_out);
        }
    }
    return 0;
}
