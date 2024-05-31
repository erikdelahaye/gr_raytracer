#ifndef METRICS_H_IMPORTED
#define METRICS_H_IMPORTED

#include "../tensors/tensor4.h"

enum Covariance {
    COVARIANT,
    CONTRAVARIANT
};

tensor4* metric_bh(enum Covariance cov, int th_derivative, tensor4* p_tensor_event, double mass_BH, double rot_param_a);

tensor4* metric_schwarzschild(enum Covariance cov, tensor4* p_tensor_event, double mass_BH);

tensor4* metric_schwarzschild_covariant(tensor4* p_tensor_event, double mass_BH);

tensor4* metric_schwarzschild_contravariant(tensor4* p_tensor_event, double mass_BH);

tensor4* metric_schwarzschild_derivative_covariant(tensor4* p_tensor_event, double mass_BH);

tensor4* metric_kerr(enum Covariance cov, tensor4* p_tensor_event, double mass_BH, double rot_param_a);

tensor4* metric_kerr_covariant(tensor4* p_tensor_event, double mass_BH, double rot_param_a);

tensor4* metric_kerr_contravariant(tensor4* p_tensor_event, double mass_BH, double rot_param_a);

tensor4* metric_kerr_derivative_covariant(tensor4* p_tensor_event, double mass_BH, double rot_param_a);

// TODO: tensor4* metric_wormhole_covariant();

#endif
