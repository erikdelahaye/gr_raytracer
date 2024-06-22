#ifndef RAYS_H_IMPORTED
#define RAYS_H_IMPORTED

#include "../tensors/tensor4.h"
#include "../evolvers/evolvers.h"
#include "../objects/objects.h"

int* cast_ray(tensor4* origin, tensor4* direction, enum Evolvers evolver, double* evolver_params, object* objects, enum Metrics metric_type, double* metric_params);

#endif
