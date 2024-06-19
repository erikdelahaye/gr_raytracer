#ifndef EVOLVERS_H
#define EVOLVERS_H

#include "../tensors/tensor4.h"
#include "../metrics/metrics.h"

enum Evolvers {
    RK4
};

tensor4** evolvers_rk4(tensor4* x_0, tensor4* v_0, double step_size, enum Metrics metric_type, double* params);

#endif
