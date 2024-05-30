#include "../tensors/tensor4.h"
#include "metrics.h"

#include <math.h>
#include <stdio.h>



tensor4* metric_bh(enum Covariance cov, int th_derivative, tensor4* p_tensor_event, double mass_BH, double rot_param_a) {
    if (cov == COVARIANT) {
        if (rot_param_a == 0) {
            if (th_derivative == 0) {
                return metric_schwarzschild_covariant(p_tensor_event, mass_BH);
            } else if (th_derivative == 1) {
                return metric_schwarzschild_derivative_covariant(p_tensor_event, mass_BH);
            } else {
                fprintf(stderr, "ERROR: metric_bh does not support the given parameters: covariant, th_derivative %d, rot_param_a %f", th_derivative, rot_param_a);
                return NULL;
            }
        } else {
            if (th_derivative == 0) {
                return metric_kerr_covariant(p_tensor_event, mass_BH, rot_param_a);
            } else {
                fprintf(stderr, "ERROR: metric_bh does not support the given parameters: covariant, th_derivative %d, rot_param_a %f", th_derivative, rot_param_a);
                return NULL;
            }
        }
    } else if (cov == CONTRAVARIANT) {
        if (rot_param_a == 0) {
            if (th_derivative == 0) {
                return metric_schwarzschild_contravariant(p_tensor_event, mass_BH);
            } else {
                fprintf(stderr, "ERROR: metric_bh does not support the given parameters: contravariant, th_derivative %d, rot_param_a %f", th_derivative, rot_param_a);
                return NULL;
            }
        } else {
            if (th_derivative == 0) {
                return metric_kerr_contravariant(p_tensor_event, mass_BH, rot_param_a);
            } else {
                fprintf(stderr, "ERROR: metric_bh does not support the given parameters: contravariant, th_derivative %d, rot_param_a %f", th_derivative, rot_param_a);
                return NULL;
            }
        }
    } else {
        fprintf(stderr, "ERROR: Covariance can only be COVARIANT OR CONTRAVARIANT.");
        return NULL;
    }
}



tensor4* metric_schwarzschild(enum Covariance cov, tensor4* p_tensor_event, double mass_BH) {
    if (cov == COVARIANT) {
        return metric_schwarzschild_covariant(p_tensor_event, mass_BH);
    } else if (cov == CONTRAVARIANT) {
        return metric_schwarzschild_contravariant(p_tensor_event, mass_BH);
    } else {
        fprintf(stderr, "ERROR: Covariance can only be COVARIANT OR CONTRAVARIANT.");
        return NULL;
    }
}


tensor4* metric_schwarzschild_covariant(tensor4* p_tensor_event, double mass_BH) {
    tensor4* p_tensor_metric = tensor4_zeros(2);

    double radius = p_tensor_event->vals[1];
    double sin_theta = sin(p_tensor_event->vals[2]);

    double minus_g_00 = 1.0 - 2.0 * mass_BH / radius;

    p_tensor_metric->vals[0] = -minus_g_00;
    p_tensor_metric->vals[5] = 1.0/minus_g_00;
    p_tensor_metric->vals[10] = radius * radius;
    p_tensor_metric->vals[15] = radius * radius * sin_theta * sin_theta;
    return p_tensor_metric;
}


tensor4* metric_schwarzschild_contravariant(tensor4* p_tensor_event, double mass_BH) {
    tensor4* p_tensor_metric = tensor4_zeros(2);

    double radius = p_tensor_event->vals[1];
    double sin_theta = sin(p_tensor_event->vals[2]);

    double minus_g_00 = 1.0 - 2.0 * mass_BH / radius;

    p_tensor_metric->vals[0] = -1.0 / minus_g_00;
    p_tensor_metric->vals[5] = minus_g_00;
    p_tensor_metric->vals[10] = 1.0 / (radius * radius);
    p_tensor_metric->vals[15] = 1.0 / (radius * radius * sin_theta * sin_theta);
    return p_tensor_metric;
}


tensor4* metric_schwarzschild_derivative_covariant(tensor4* p_tensor_event, double mass_BH) {
    tensor4* p_tensor_metric = tensor4_zeros(3);

    double radius = p_tensor_event->vals[1];
    double sin_theta = sin(p_tensor_event->vals[2]);
    double cos_theta = cos(p_tensor_event->vals[2]);

    p_tensor_metric->vals[16] = -2.0 * mass_BH / (radius * radius); // 0,0,1
    p_tensor_metric->vals[21] = 2.0 * mass_BH / (radius * radius * (1.0 - 2.0 * mass_BH / radius) * (1.0 - 2.0 * mass_BH / radius)); // 1,1,1
    p_tensor_metric->vals[26] = 2.0 * radius; // 2,2,1
    p_tensor_metric->vals[31] = 2.0 * radius * sin_theta * sin_theta; // 3,3,1
    p_tensor_metric->vals[47] = 2.0 * radius * radius * sin_theta * cos_theta; // 3,3,2
    return p_tensor_metric;
}


tensor4* metric_kerr(enum Covariance cov, tensor4* p_tensor_event, double mass_BH, double rot_param_a) {
    if (cov == COVARIANT) {
        return metric_kerr_covariant(p_tensor_event, mass_BH, rot_param_a);
    } else if (cov == CONTRAVARIANT) {
        return metric_kerr_contravariant(p_tensor_event, mass_BH, rot_param_a);
    } else {
        fprintf(stderr, "ERROR: Covariance can only be COVARIANT OR CONTRAVARIANT.");
        return NULL;
    }
}


tensor4* metric_kerr_covariant(tensor4* p_tensor_event, double mass_BH, double rot_param_a) {
    if (rot_param_a > mass_BH) {
        fprintf(stderr, "WARNING: Rotational parameter a exceeds BH mass. This would result in a naked singularity.");
    }

    tensor4* p_tensor_metric = tensor4_zeros(2);

    double radius = p_tensor_event->vals[1];
    double sin_theta = sin(p_tensor_event->vals[2]);
    double cos_theta = cos(p_tensor_event->vals[2]);

    double sigma = radius * radius + rot_param_a * rot_param_a * cos_theta * cos_theta;
    double delta = radius * radius - 2.0 * mass_BH * radius + rot_param_a * rot_param_a;

    p_tensor_metric->vals[0] = 2.0 * mass_BH * radius / sigma - 1; // t-t
    p_tensor_metric->vals[5] = sigma / delta; // r-r
    p_tensor_metric->vals[10] = sigma; // theta-theta
    p_tensor_metric->vals[15] = (radius * radius + rot_param_a * rot_param_a + 2.0 * mass_BH * radius * rot_param_a * rot_param_a / sigma * sin_theta * sin_theta) * sin_theta * sin_theta; // phi-phi

    p_tensor_metric->vals[3] = -2.0 * mass_BH * radius * rot_param_a * sin_theta * sin_theta / sigma; // t-phi
    p_tensor_metric->vals[12] = p_tensor_metric->vals[3]; // phi-t
    return p_tensor_metric;
}


tensor4* metric_kerr_contravariant(tensor4* p_tensor_event, double mass_BH, double rot_param_a) {
    if (rot_param_a > mass_BH) {
        fprintf(stderr, "WARNING: Rotational parameter a exceeds BH mass. This would result in a naked singularity.");
    }

    tensor4* p_tensor_metric = tensor4_zeros(2);

    double radius = p_tensor_event->vals[1];
    double sin_theta = sin(p_tensor_event->vals[2]);
    double cos_theta = cos(p_tensor_event->vals[2]);

    double sigma = radius * radius + rot_param_a * rot_param_a * cos_theta * cos_theta;
    double delta = radius * radius - 2.0 * mass_BH * radius + rot_param_a * rot_param_a;

    p_tensor_metric->vals[0] = -(radius * radius + rot_param_a * rot_param_a + 2.0 * mass_BH * radius * rot_param_a * rot_param_a / sigma * sin_theta * sin_theta) / delta; // t-t
    p_tensor_metric->vals[5] = delta / sigma; // r-r
    p_tensor_metric->vals[10] = 1.0 / sigma; // theta-theta
    p_tensor_metric->vals[15] = (1 - 2.0 * mass_BH * radius / sigma) / (delta * sin_theta * sin_theta); // phi-phi

    p_tensor_metric->vals[3] = -2.0 * mass_BH * radius * rot_param_a / (sigma * delta); // t-phi
    p_tensor_metric->vals[12] = p_tensor_metric->vals[3]; // phi-t
    return p_tensor_metric;
}
