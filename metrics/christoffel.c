#include <string.h>
#include <stdlib.h>

#include "../metrics/metrics.h"
#include "../util/constants.h"

tensor4* christoffel_symbols(enum Metrics metric_type, tensor4* p_tensor_event, double* params) {
    // Gamma^sigma_mu-nu = 1/2 g^sigma-rho (g_rho-mu,nu + g_rho-nu,mu - g_mu-nu,rho)

    tensor4* p_metric_contravariant = metric(metric_type, CONTRAVARIANT, 0, p_tensor_event, params);

    tensor4* p_metric_derivative = metric(metric_type, COVARIANT, 1, p_tensor_event, params);

    tensor4* p_sum_2 = tensor4_reorder(p_metric_derivative, "rnm", "rmn");

    tensor4* p_sum_3_neg = tensor4_reorder(p_metric_derivative, "mnr", "rmn");
    tensor4* p_sum_3 = tensor4_scalar_mult(p_sum_3_neg, -1.0);

    tensor4* p_sum_12 = tensor4_add(p_metric_derivative, p_sum_2);
    tensor4* p_sum = tensor4_add(p_sum_12, p_sum_3);

    tensor4* pp_tensors[2] = {p_metric_contravariant, p_sum};

    tensor4* p_2_tensor_out = tensor4_mult(pp_tensors, "srrmn", 2);
    tensor4* p_tensor_out = tensor4_scalar_mult(p_2_tensor_out, 0.5);

    tensor4_free(p_metric_contravariant);
    tensor4_free(p_metric_derivative);
    tensor4_free(p_sum_2);
    tensor4_free(p_sum_3_neg);
    tensor4_free(p_sum_3);
    tensor4_free(p_sum_12);
    tensor4_free(p_sum);
    tensor4_free(p_2_tensor_out);
    return p_tensor_out;
}


tensor4* christoffel_symbols_derivative(enum Metrics metric_type, tensor4* p_tensor_event, double* params) {
    tensor4** christ_diff = malloc(4*sizeof(tensor4*));

    tensor4** pp_tensor_diff_steps = tensor4_diff_steps();

    for (int i = 0; i < 4; i++) {
        tensor4* p_tensor_event_plus = tensor4_add(p_tensor_event, pp_tensor_diff_steps[i]);
        tensor4* p_tensor_event_minus = tensor4_subtract(p_tensor_event, pp_tensor_diff_steps[i]);

        tensor4* christ_plus = christoffel_symbols(metric_type, p_tensor_event_plus, params);
        tensor4* christ_minus = christoffel_symbols(metric_type, p_tensor_event_minus, params);

        tensor4* christ_difference_i = tensor4_subtract(christ_plus, christ_minus);

        christ_diff[i] = tensor4_scalar_mult(christ_difference_i, 0.5 / DIFF_STEP);

        tensor4_free(pp_tensor_diff_steps[i]);
        tensor4_free(p_tensor_event_plus);
        tensor4_free(p_tensor_event_minus);
        tensor4_free(christ_plus);
        tensor4_free(christ_minus);
        tensor4_free(christ_difference_i);
    }

    free(pp_tensor_diff_steps);


    tensor4* p_tens_out = tensor4_zeros(4);

    for (int i = 0; i < 4; i++) {
        memcpy(p_tens_out->vals + i*64, christ_diff[i]->vals, 64*sizeof(double));
        tensor4_free(christ_diff[i]);
    }

    free(christ_diff);

    return p_tens_out;
}
