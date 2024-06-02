#ifndef CURVATURE_H
#define CURVATURE_H

#include "../tensors/tensor4.h"
#include "christoffel.h"
#include "metrics.h"

tensor4* riemann_tensor(enum Metrics metric_type, tensor4* p_tensor_event, double* params);

tensor4* ricci_tensor(enum Metrics metric_type, tensor4* p_tensor_event, double* params);

double ricci_scalar(enum Metrics metric_type, tensor4* p_tensor_event, double* params);

#endif
