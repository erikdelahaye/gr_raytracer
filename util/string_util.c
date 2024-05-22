#include "string_util.h"

#include <stdio.h>

int remove_spaces(char* input) {
    int offset = 0, 
        i = 0;
    do {
        while (input[i+offset] == ' ') {
            offset++;
        }
        input[i] = input[i+offset];
        i++;
    } while (input[i+offset-1] != '\0');
    return 0;
}


int print_tensor(tensor4* p_tensor) {
    switch (p_tensor->rank) {
        case 0:
            printf("(%f)\n", p_tensor->vals[0]);
            break;
        case 1:
            printf("(%f)\n(%f)\n(%f)\n(%f)\n", p_tensor->vals[0], p_tensor->vals[1], p_tensor->vals[2], p_tensor->vals[3]);
            break;
        case 2:
            printf("(%f,  %f,  %f,  %f)\n", p_tensor->vals[0], p_tensor->vals[4], p_tensor->vals[8], p_tensor->vals[12]);
            printf("(%f,  %f,  %f,  %f)\n", p_tensor->vals[1], p_tensor->vals[5], p_tensor->vals[9], p_tensor->vals[13]);
            printf("(%f,  %f,  %f,  %f)\n", p_tensor->vals[2], p_tensor->vals[6], p_tensor->vals[10], p_tensor->vals[14]);
            printf("(%f,  %f,  %f,  %f)\n", p_tensor->vals[3], p_tensor->vals[7], p_tensor->vals[11], p_tensor->vals[15]);
            break;
        default:
            fprintf(stderr, "ERROR: Printing tensors is only supported up to rank 2.");
    }
    return 0;
}
