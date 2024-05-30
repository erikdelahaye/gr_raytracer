#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../util/string_util.h"
#include "../util/array_util.h"

tensor4* tensor4_zeros(int rank) {
    tensor4* p_tensor_out = malloc(sizeof(tensor4));

    int num_entries = (int) pow(4.0, (double) rank);
    double* entries = calloc(num_entries, sizeof(double));

    p_tensor_out->rank = rank;
    p_tensor_out->vals = entries;
    return p_tensor_out;
}


tensor4* tensor4_add(tensor4* p_tensor_a, tensor4* p_tensor_b) {
    if (p_tensor_a->rank != p_tensor_b->rank) {
        fprintf(stderr, "tensor4_add recieved tensors of different ranks\n");
        return NULL;
    }

    tensor4* p_tensor_out = tensor4_zeros(p_tensor_a->rank);

    int num_entries = pow(4.0, (double) p_tensor_a->rank);

    for (int i = 0; i < num_entries; i++) {
        p_tensor_out->vals[i] = p_tensor_a->vals[i] + p_tensor_b->vals[i];
    }

    return p_tensor_out;
}


tensor4* tensor4_mult(tensor4** pp_tensors, char* indices, int num) {
    indices = remove_spaces(indices);
    
    int second_occurrence = 1,
        num_double_occurrences = 0;

    int** double_occurrences = malloc(sizeof(int*));

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

    tensor4* p_tensor_out = tensor4_zeros(output_rank);

    int* output_indices = malloc(output_rank * sizeof(int));

    tensor4_mult_recursive_output_indexing(output_indices, 0, pp_tensors, num, double_occurrences, num_double_occurrences, &p_tensor_out);
    return p_tensor_out;
}


int tensor4_mult_recursive_output_indexing(int* output_indices, int recursion_depth, tensor4** pp_tensors, int num, int** double_occurrences, int num_double_occurrences, tensor4** pp_tensor_out) {
    if (recursion_depth == (*pp_tensor_out)->rank) {
        int* sum_indices = malloc(num_double_occurrences * sizeof(int));
        tensor4_mult_recursive_sum_indexing(output_indices, sum_indices, 0, pp_tensors, num, double_occurrences, num_double_occurrences, pp_tensor_out);
    } else {
        for (int i = 0; i < 4; i++) {
            output_indices[recursion_depth] = i;
            tensor4_mult_recursive_output_indexing(output_indices, recursion_depth+1, pp_tensors, num, double_occurrences, num_double_occurrences, pp_tensor_out);
        }
    }
    return 0;
}


int tensor4_mult_recursive_sum_indexing(int* output_indices, int* sum_indices, int recursion_depth, tensor4** pp_tensors, int num, int** double_occurrences, int num_double_occurrences, tensor4** pp_tensor_out) {
    if (recursion_depth == num_double_occurrences) {
        // build array of indices
        int total_indices = (*pp_tensor_out)->rank + 2*num_double_occurrences;
        int indices[total_indices];

        int next_output_index = 0;
        for (int i = 0; i < total_indices; i++) {
            indices[i] = output_indices[next_output_index];
            next_output_index++;
            for (int j = 0; j < num_double_occurrences; j++) {
                if (i == double_occurrences[j][0] || i == double_occurrences[j][1]) {
                    indices[i] = sum_indices[j];
                    next_output_index--;
                }
            }
        }

        double temp_addend = 1;
        double temp_val;
        int used_indices = 0;
        for (int i = 0; i < num; i++) {
            temp_val = tensor4_at_array(pp_tensors[i], indices+used_indices);
            temp_addend *= temp_val;
            used_indices += pp_tensors[i]->rank;
        }

        int output_index = array_index_from_index_array(output_indices, (*pp_tensor_out)->rank);

        (*pp_tensor_out)->vals[output_index] += temp_addend;
    } else {
        for (int i = 0; i < 4; i++) {
            sum_indices[recursion_depth] = i;
            tensor4_mult_recursive_sum_indexing(output_indices, sum_indices, recursion_depth+1, pp_tensors, num, double_occurrences, num_double_occurrences, pp_tensor_out);
        }

    }
    return 0;
}


double tensor4_at_array(tensor4* p_tensor, int* indices) {
    int index = array_index_from_index_array(indices, p_tensor->rank);
    return p_tensor->vals[index];
}


tensor4* tensor4_scalar_mult(tensor4* p_tensor, double factor) {
    tensor4* p_tensor_out = tensor4_zeros(p_tensor->rank);
    for (int i = 0; i < pow(4.0, (double) p_tensor->rank); i++) {
        p_tensor_out->vals[i] = factor * p_tensor->vals[i];
    }
    return p_tensor_out;
}


tensor4* tensor4_reorder(tensor4* p_tensor, char* indices_in, char* indices_out) {
    tensor4* p_tensor_out = tensor4_zeros(p_tensor->rank);

    int reorder_instructions[p_tensor->rank];
    int indices_old[p_tensor->rank];
    int indices_new[p_tensor->rank];

    for (int i = 0; i < p_tensor->rank; i++) {
        reorder_instructions[i] = (int) (strchr(indices_out, indices_in[i]) - indices_out);
    }

    tensor4_reorder_recursive(p_tensor, indices_old, indices_new, reorder_instructions, 0, p_tensor_out);
    return p_tensor_out;
}


int tensor4_reorder_recursive(tensor4* p_tensor, int* indices_old, int* indices_new, int* reorder_instructions, int recursion_depth, tensor4* p_tensor_out) {
if (recursion_depth == p_tensor->rank) {
    int index_old = array_index_from_index_array(indices_old, recursion_depth);
    int index_new = array_index_from_index_array(indices_new, recursion_depth);

    p_tensor_out->vals[index_new] = p_tensor->vals[index_old];
} else {
    for (int i = 0; i < 4; i++) {
        indices_old[recursion_depth] = i;
        indices_new[reorder_instructions[recursion_depth]] = i;
        tensor4_reorder_recursive(p_tensor, indices_old, indices_new, reorder_instructions, recursion_depth+1, p_tensor_out);
    }
}

return 0;
}
