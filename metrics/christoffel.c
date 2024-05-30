#include "../metrics/metrics.h"

tensor4* christoffel_symbols(tensor4* p_metric_contravariant, tensor4* p_metric_derivative) {
    // Gamma^sigma_mu-nu = 1/2 g^sigma-rho (g_rho-mu,nu + g_rho-nu,mu - g_mu-nu,rho)

    tensor4* p_sum_2 = tensor4_reorder(p_metric_derivative, "rmn", "rnm");

    tensor4* p_sum_3 = tensor4_reorder(p_metric_derivative, "rmn", "mnr");
    p_sum_3 = tensor4_scalar_mult(p_sum_3, -1.0);

    tensor4* p_sum = tensor4_add(p_metric_derivative, p_sum_2);
    p_sum = tensor4_add(p_sum, p_sum_3);

    tensor4* pp_tensors[2] = {p_metric_contravariant, p_sum};

    tensor4* p_tensor_out = tensor4_mult(pp_tensors, "srrmn", 2);
    p_tensor_out = tensor4_scalar_mult(p_tensor_out, 0.5);
    return 0;
}
