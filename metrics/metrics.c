#include "../tensors/tensor4.h"
#include <math.h>
#include <stdio.h>

int metric_schwarzschild(tensor4* p_tensor_event, double mass_BH, tensor4** pp_tensor_metric) {
    (*pp_tensor_metric) = tensor4_zeros(2);

    double radius = p_tensor_event->vals[1];
    double sin_theta = sin(p_tensor_event->vals[2]);

    double minus_g00 = 1.0 - 2.0 * mass_BH / radius;

    (*pp_tensor_metric)->vals[0] = -minus_g00;
    (*pp_tensor_metric)->vals[5] = 1.0/minus_g00;
    (*pp_tensor_metric)->vals[10] = radius * radius;
    (*pp_tensor_metric)->vals[15] = radius * radius * sin_theta * sin_theta;
    return 0;
}


int metric_kerr(tensor4* p_tensor_event, double mass_BH, double rot_param_a, tensor4** pp_tensor_metric) {
    if (rot_param_a > mass_BH) {
        fprintf(stderr, "WARNING: Rotational parameter a exceeds BH mass. This would result in a naked singularity.");
    }

    (*pp_tensor_metric) = tensor4_zeros(2);

    double radius = p_tensor_event->vals[1];
    double sin_theta = sin(p_tensor_event->vals[2]);
    double cos_theta = cos(p_tensor_event->vals[2]);

    double sigma = radius * radius + rot_param_a * rot_param_a * cos_theta * cos_theta;
    double delta = radius * radius - 2.0 * mass_BH * radius + rot_param_a * rot_param_a;

    (*pp_tensor_metric)->vals[0] = 2.0 * mass_BH * radius / sigma - 1;
    (*pp_tensor_metric)->vals[5] = sigma / delta;
    (*pp_tensor_metric)->vals[10] = sigma;
    (*pp_tensor_metric)->vals[15] = (radius * radius + rot_param_a * rot_param_a + 2.0 * mass_BH * radius * rot_param_a * rot_param_a / sigma * sin_theta * sin_theta) * sin_theta * sin_theta;

    (*pp_tensor_metric)->vals[1] = -2.0 * mass_BH * radius * rot_param_a * sin_theta * sin_theta / sigma;
    (*pp_tensor_metric)->vals[4] = (*pp_tensor_metric)->vals[1];
    return 0;
}
