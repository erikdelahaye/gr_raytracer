#ifndef CHRISTOFFEL_H
#define CHRISTOFFEL_H

#include "../tensors/tensor4.h"
#include "metrics.h"

tensor4* christoffel_symbols(enum Metrics metric_type, tensor4* p_tensor_event, double* params);

tensor4* christoffel_symbols_derivative(enum Metrics metric_type, tensor4* p_tensor_event, double* params);

#endif
