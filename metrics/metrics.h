#ifndef METRICS_H_IMPORTED
#define METRICS_H_IMPORTED

#include "../tensors/tensor4.h"

enum Covariance {
    COVARIANT,
    CONTRAVARIANT
};

int metric_schwarzschild(enum Covariance cov, tensor4* p_tensor_event, double mass_BH, tensor4** pp_tensor_metric);

int metric_schwarzschild_covariant(tensor4* p_tensor_event, double mass_BH, tensor4** pp_tensor_metric);

int metric_schwarzschild_contravariant(tensor4* p_tensor_event, double mass_BH, tensor4** pp_tensor_metric);

int metric_kerr_covariant(tensor4* p_tensor_event, double mass_BH, double rot_param_a, tensor4** pp_tensor_metric);

// TODO: int metric_wormhole_covariant();

#endif
