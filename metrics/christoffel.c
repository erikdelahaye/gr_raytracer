#include <string.h>
#include <stdlib.h>

#include "../metrics/metrics.h"
#include "../util/constants.h"

tensor4* christoffel_symbols(enum Metrics metric_type, tensor4* p_tensor_event, double* params) {
    // Gamma^sigma_mu-nu = 1/2 g^sigma-rho (g_rho-mu,nu + g_rho-nu,mu - g_mu-nu,rho)

    tensor4* p_metric_contravariant = metric(metric_type, CONTRAVARIANT, 0, p_tensor_event, params);

    tensor4* p_metric_derivative = metric(metric_type, COVARIANT, 1, p_tensor_event, params);

    tensor4* p_sum_2 = tensor4_reorder(p_metric_derivative, "rnm", "rmn");

    tensor4* p_sum_3 = tensor4_reorder(p_metric_derivative, "mnr", "rmn");
    p_sum_3 = tensor4_scalar_mult(p_sum_3, -1.0);

    tensor4* p_sum = tensor4_add(p_metric_derivative, p_sum_2);
    p_sum = tensor4_add(p_sum, p_sum_3);

    tensor4* pp_tensors[2] = {p_metric_contravariant, p_sum};

    tensor4* p_tensor_out = tensor4_mult(pp_tensors, "srrmn", 2);
    p_tensor_out = tensor4_scalar_mult(p_tensor_out, 0.5);
    return p_tensor_out;
}


tensor4* christoffel_symbols_derivative(enum Metrics metric_type, tensor4* p_tensor_event, double* params) {
    tensor4** christ_diff = malloc(4*sizeof(tensor4*));

    for (int i = 0; i < 4; i++) {
        christ_diff[i] = tensor4_scalar_mult(
                             tensor4_subtract(
                                 christoffel_symbols(
                                     metric_type, 
                                     tensor4_add(
                                         p_tensor_event, 
                                         tensor4_diff_steps()[i]), 
                                     params), 
                                 christoffel_symbols(
                                     metric_type, 
                                     tensor4_subtract(
                                         p_tensor_event, 
                                         tensor4_diff_steps()[i]), 
                                     params)), 
                             0.5 / DIFF_STEP);
    }

    tensor4* p_tens_out = tensor4_zeros(4);

    memcpy(p_tens_out->vals, christ_diff[0]->vals, 64*sizeof(double));
    memcpy(p_tens_out->vals+64, christ_diff[1]->vals, 64*sizeof(double));
    memcpy(p_tens_out->vals+128, christ_diff[2]->vals, 64*sizeof(double));
    memcpy(p_tens_out->vals+192, christ_diff[3]->vals, 64*sizeof(double));

    return p_tens_out;
}
