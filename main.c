#include <stdio.h>
#include <stdlib.h>

#include "tensors/tensor4.h"

int main(int argc, char** argv) {
    /*
    tensor4* p_a = malloc(sizeof(tensor4));
    tensor4* p_b = malloc(sizeof(tensor4));
    tensor4* p_c = malloc(sizeof(tensor4));

    p_a->rank = 1;
    p_b->rank = 1;
    double vals_a[4] = {1.5, 2.0, 1.0, 2.5}, vals_b[4] = {1.0, 2.0, 3.0, 4.0};

    p_a->vals = vals_a;
    p_b->vals = vals_b;

    tensor4_add(p_a, p_b, p_c);

    printf("Rank is %d, entries are %f, %f, %f, %f.\n", p_c->rank, p_c->vals[0], p_c->vals[1], p_c->vals[2], p_c->vals[3]);
    */
    tensor4* p_tens_a = tensor4_zeros(4);
    tensor4* p_tens_b = tensor4_zeros(3);

    tensor4** pp_tens_in = malloc(2*sizeof(tensor4*));

    pp_tens_in[0] = p_tens_a;
    pp_tens_in[1] = p_tens_b;

    tensor4** pp_tens_out = malloc(sizeof(tensor4*));


    char indices[] = "ijkl lmn";
    tensor4_mult(pp_tens_in, indices, 2, pp_tens_out);
    printf("%d", pp_tens_out[0]->rank);
    
    return 0;
}
