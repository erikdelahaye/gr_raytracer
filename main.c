#include <stdio.h>
#include <stdlib.h>

#include "tensors/tensor4.h"
#include "metrics/metrics.h"
#include "metrics/christoffel.h"
#include "util/string_util.h"

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

    /*
    tensor4* p_tens_a = tensor4_zeros(2);
    tensor4* p_tens_b = tensor4_zeros(1);

    p_tens_a->vals[0] = 3; // i=0, j=0
    p_tens_a->vals[1] = 2; // i=1, j=0
    p_tens_a->vals[2] = 3; // i=2, j=0
    p_tens_a->vals[3] = 2; // i=3, j=0
    p_tens_a->vals[5] = 1;
    p_tens_a->vals[10] = 1;
    p_tens_a->vals[15] = 1;

    p_tens_b->vals[0] = 1;
    p_tens_b->vals[1] = 2;
    p_tens_b->vals[2] = 3;
    p_tens_b->vals[3] = 4;

    tensor4** pp_tens_in = malloc(2*sizeof(tensor4*));

    pp_tens_in[0] = p_tens_a;
    pp_tens_in[1] = p_tens_b;

    tensor4** pp_tens_out = malloc(sizeof(tensor4*));


    char indices[] = "ij j";
    tensor4_mult(pp_tens_in, indices, 2, pp_tens_out);

    print_tensor(*pp_tens_out);

    */

    /*
    tensor4* p_tens_a = tensor4_zeros(2);
    p_tens_a->vals[2] = 2;
    p_tens_a->vals[9] = 5;
    //tensor4** pp_tens_new;
    //tensor4** pp_tens_reordered;
    //tensor4** pp_tens_new = malloc(sizeof(tensor4*));
    tensor4** pp_tens_reordered = malloc(sizeof(tensor4*));

    //tensor4_scalar_mult(p_tens_a, 3.0, pp_tens_new);

    tensor4_reorder(p_tens_a, "ij", "ji", pp_tens_reordered);
    
    print_tensor(p_tens_a);
    printf("\n");
    print_tensor(*pp_tens_reordered);
    */

    /*
    tensor4* event = tensor4_zeros(1);

    event->vals[1] = 12.0;
    event->vals[2] = 3.1415/2.0;
    
    tensor4* metric = metric_bh(CONTRAVARIANT, 0, event, 10.0, 0.0);

    tensor4* metric_derivative = metric_bh(COVARIANT, 1, event, 10.0, 0.0);

    tensor4* christ = christoffel_symbols(metric, metric_derivative);

    christ = tensor4_reorder(christ, "ijk", "jki");
    
    christ->rank = 2;
    print_tensor(christ);
    printf("\n");

    christ->vals += 16;
    print_tensor(christ);
    printf("\n");

    christ->vals += 16;
    print_tensor(christ);
    printf("\n");

    christ->vals += 16;
    print_tensor(christ);
    printf("\n");
    */

    return 0;
}
