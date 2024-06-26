#include "../tensors/tensor4.h"
#include "metrics.h"

#include <math.h>
#include <stdio.h>


tensor4* metric(enum Metrics metric_type, enum Covariance cov, int th_derivative, tensor4* p_tensor_event, double* params) {
    switch (metric_type) {
        case BH: // params: mass_BH, rot_param_a
            return metric_bh(cov, th_derivative, p_tensor_event, params[0], params[1]);

        case SCHWARZSCHILD: // params: mass_BH
            return metric_bh(cov, th_derivative, p_tensor_event, params[0], 0.0);

        case KERR: // params: mass_BH, rot_param_a
            return metric_bh(cov, th_derivative, p_tensor_event, params[0], params[1]);

        case MINKOWSKI:
            return metric_minkowski(th_derivative);

        default:
            fprintf(stderr, "ERROR: metric type not recognised\n");
            return NULL;
    }
}


tensor4* metric_numerical_derivative(enum Metrics metric_type, enum Covariance cov, int th_derivative, tensor4* p_tensor_event, double* params) {
    // TODO
    fprintf(stderr, "ERROR: metric_numerical_derivative not implemented");
    return NULL;
}


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
            } else if (th_derivative == 1) {
                return metric_kerr_derivative_covariant(p_tensor_event, mass_BH, rot_param_a);
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


tensor4* metric_kerr_derivative_covariant(tensor4* p_tensor_event, double mass_BH, double rot_param_a) {
    if (rot_param_a > mass_BH) {
        fprintf(stderr, "WARNING: Rotational parameter a exceeds BH mass. This would result in a naked singularity.");
    }

    tensor4* p_tensor_metric = tensor4_zeros(3);

    double radius = p_tensor_event->vals[1];
    double sin_theta = sin(p_tensor_event->vals[2]);
    double cos_theta = cos(p_tensor_event->vals[2]);

    double sigma = radius * radius + rot_param_a * rot_param_a * cos_theta * cos_theta;
    double delta = radius * radius - 2.0 * mass_BH * radius + rot_param_a * rot_param_a;
    double dsigma_dtheta = -2.0 * rot_param_a * rot_param_a * cos_theta * sin_theta;

    p_tensor_metric->vals[16] = 2.0 * mass_BH / sigma - 4.0 * mass_BH * radius * radius / (sigma * sigma); // t-t,r 
    p_tensor_metric->vals[21] = 2.0 * radius / delta + 2.0 * (mass_BH - radius) * sigma / (delta * delta); // r-r,r
    p_tensor_metric->vals[26] = 2.0 * radius; // theta-theta,r
    p_tensor_metric->vals[31] = (2.0 * radius + (2.0 - 4.0 * radius * radius / sigma) * mass_BH * rot_param_a * rot_param_a * sin_theta * sin_theta / sigma) * sin_theta * sin_theta; // phi-phi,r
    p_tensor_metric->vals[19] = (4.0 * radius * radius / sigma - 2.0) * sin_theta * sin_theta * mass_BH * rot_param_a / sigma; // t-phi,r
    p_tensor_metric->vals[28] = p_tensor_metric->vals[19]; // phi-t,r

    p_tensor_metric->vals[32] = -2.0 * mass_BH * radius * dsigma_dtheta / (sigma * sigma); // t-t,theta 
    p_tensor_metric->vals[37] = dsigma_dtheta / delta; // r-r,theta
    p_tensor_metric->vals[42] = dsigma_dtheta; // theta-theta,theta
    p_tensor_metric->vals[47] = 2.0 * sin_theta * cos_theta * (radius * radius + rot_param_a * rot_param_a + 2.0 * mass_BH * radius * rot_param_a * rot_param_a * sin_theta * sin_theta / sigma) + (4.0 * cos_theta - 2.0 * sin_theta * dsigma_dtheta / sigma) * mass_BH * radius * rot_param_a * rot_param_a * sin_theta * sin_theta * sin_theta / sigma; // phi-phi,theta
    p_tensor_metric->vals[35] = (2.0 * sin_theta * dsigma_dtheta / sigma - 4.0 * cos_theta) * mass_BH * radius * rot_param_a * sin_theta / sigma; // t-phi,theta
    p_tensor_metric->vals[44] = p_tensor_metric->vals[35]; // phi-t,theta
    return p_tensor_metric;
}


tensor4* metric_minkowski(int th_derivative) {
    if (th_derivative == 0) {
        tensor4* p_tens_out = tensor4_zeros(2);
        p_tens_out->vals[0] = -1.0;
        p_tens_out->vals[5] = 1.0;
        p_tens_out->vals[10] = 1.0;
        p_tens_out->vals[15] = 1.0;
        return p_tens_out;
    } else if (th_derivative >= 1) {
        tensor4* p_tens_out = tensor4_zeros(3);
        return p_tens_out;
    }

    return NULL;
}
