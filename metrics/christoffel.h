#ifndef CHRISTOFFEL_H
#define CHRISTOFFEL_H

#include "../tensors/tensor4.h"

tensor4* christoffel_symbols(tensor4* p_metric_contravariant, tensor4* p_metric_derivative);

#endif
