#include "../metrics/metrics.h"

int christoffel_symbols(tensor4* p_metric_contravariant, tensor4* p_metric_derivative, tensor4** pp_tensor_out) {
    // Gamma^sigma_mu-nu = 1/2 g^sigma-rho (g_rho-mu,nu + g_rho-nu,mu - g_mu-nu,rho)
    tensor4** pp_sum_2;
    tensor4** pp_sum_3;
    tensor4** pp_sum_3_neg;

    tensor4_reorder(p_metric_derivative, "rmn", "rnm", pp_sum_2);
    tensor4_reorder(p_metric_derivative, "rmn", "mnr", pp_sum_3);

    tensor4_scalar_mult(*pp_sum_3, -1.0, pp_sum_3_neg);

    tensor4* p_sum = tensor4_zeros(3);

    tensor4_add(p_metric_derivative, *pp_sum_2, p_sum);
    tensor4_add(p_sum, *pp_sum_3_neg, p_sum);

    tensor4* pp_tensors[2] = {p_metric_contravariant, p_sum};

    tensor4** pp_tensor_product;

    tensor4_mult(pp_tensors, "srrmn", 2, pp_tensor_product);
    tensor4_scalar_mult(*pp_tensor_product, 0.5, pp_tensor_out);
    return 0;
}
