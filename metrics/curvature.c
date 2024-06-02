#include <stdlib.h>

#include "curvature.h"


tensor4* riemann_tensor(enum Metrics metric_type, tensor4* p_tensor_event, double* params) {
    /*
    LEGEND: R -> riemann_tensor, G -> christoffel_symbol
    R^alpha_beta-mu-nu = G^alpha_beta-nu,mu - G^alpha_beta-mu,nu + G^alpha_sigma-mu * G^sigma_nu-beta - G^alpha_sigma-nu * G^sigma_mu-beta

    below:
    out = term_1 - term_2 + term_3 - term_4
        = sum_12 + term_3 - term_4
        = sum_123 - term_4
    */

    tensor4* christoffel = christoffel_symbols(metric_type, p_tensor_event, params);

    tensor4* term_2 = christoffel_symbols_derivative(metric_type, p_tensor_event, params);
    tensor4* term_1 = tensor4_reorder(term_2, "abnm", "abmn");

    tensor4* term_3_4_factors[] = {christoffel, christoffel};

    tensor4* term_3_unordered = tensor4_mult(term_3_4_factors, "asm snb", 2);
    tensor4* term_3 = tensor4_reorder(term_3_unordered, "amnb", "abmn");

    tensor4* term_4_unordered = tensor4_mult(term_3_4_factors, "asn smb", 2);
    tensor4* term_4 = tensor4_reorder(term_4_unordered, "anmb", "abmn");

    tensor4* sum_12 = tensor4_subtract(term_1, term_2);
    tensor4* sum_123 = tensor4_add(sum_12, term_3);

    tensor4* p_tensor_out = tensor4_subtract(sum_123, term_4);
    
    tensor4_free(christoffel);
    tensor4_free(term_1);
    tensor4_free(term_2);
    tensor4_free(term_3);
    tensor4_free(term_4);
    tensor4_free(term_3_unordered);
    tensor4_free(term_4_unordered);
    tensor4_free(sum_12);
    tensor4_free(sum_123);

    return p_tensor_out;
}


tensor4* ricci_tensor(enum Metrics metric_type, tensor4* p_tensor_event, double* params) {
    tensor4* riemann = riemann_tensor(metric_type, p_tensor_event, params);

    tensor4* ricci = tensor4_mult(&riemann, "aban", 1);

    tensor4_free(riemann);
    return ricci;
}


double ricci_scalar(enum Metrics metric_type, tensor4* p_tensor_event, double* params) {
    tensor4* metric_contravariant = metric(metric_type, CONTRAVARIANT, 0, p_tensor_event, params);
    tensor4* riemann = riemann_tensor(metric_type, p_tensor_event, params);

    tensor4* factors[] = {metric_contravariant, riemann};

    tensor4* ricci = tensor4_mult(factors, "bn aban", 2);

    double ricci_scalar = ricci->vals[0];

    tensor4_free(metric_contravariant);
    tensor4_free(riemann);
    tensor4_free(ricci);

    return ricci_scalar;
}
