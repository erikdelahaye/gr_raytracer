#ifndef METRICS_H_IMPORTED
#define METRICS_H_IMPORTED

#include "../tensors/tensor4.h"

int metric_schwarzschild(tensor4* p_tensor_event, double mass_BH, tensor4** pp_tensor_metric);

int metric_kerr(tensor4* p_tensor_event, double mass_BH, double rot_param_a, tensor4** pp_tensor_metric);

// TODO: int metric_wormhole();

#endif
