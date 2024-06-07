#include "evolvers.h"
#include "../metrics/christoffel.h"

#include <stdlib.h>

tensor4** evolvers_rk4(tensor4* x_0, tensor4* v_0, double step_size, enum Metrics metric_type, double* params) {
    /*
        v'^mu = -christ(x)^mu_alpha-beta v^alpha v^beta
        x'^nu = v^mu
    */

    // k1:
    tensor4* christ_1 = christoffel_symbols(metric_type, x_0, params);

    tensor4* input_k1_v[] = {christ_1, v_0, v_0};

    tensor4* minus_k1_v = tensor4_mult(input_k1_v, "mabab", 3);
    tensor4* k1_v = tensor4_scalar_mult(minus_k1_v, -1.0);

    tensor4* k1_x = tensor4_copy(v_0);


    tensor4_free(christ_1);
    tensor4_free(minus_k1_v);



    // k2:
    tensor4* h2_k1_x = tensor4_scalar_mult(k1_x, 0.5*step_size);
    tensor4* h2_k1_v = tensor4_scalar_mult(k1_v, 0.5*step_size);

    tensor4* x_1 = tensor4_add(x_0, h2_k1_x);
    tensor4* v_1 = tensor4_add(v_0, h2_k1_v);

    tensor4* christ_2 = christoffel_symbols(metric_type, x_1, params);

    tensor4* input_k2_v[] = {christ_2, v_1, v_1};

    tensor4* minus_k2_v = tensor4_mult(input_k2_v, "mabab", 3);
    tensor4* k2_v = tensor4_scalar_mult(minus_k2_v, -1.0);

    tensor4* k2_x = tensor4_copy(v_1);


    tensor4_free(h2_k1_x);
    tensor4_free(h2_k1_v);
    tensor4_free(x_1);
    tensor4_free(v_1);
    tensor4_free(christ_2);
    tensor4_free(minus_k2_v);



    // k3:
    tensor4* h2_k2_x = tensor4_scalar_mult(k2_x, 0.5*step_size);
    tensor4* h2_k2_v = tensor4_scalar_mult(k2_v, 0.5*step_size);

    tensor4* x_2 = tensor4_add(x_0, h2_k2_x);
    tensor4* v_2 = tensor4_add(v_0, h2_k2_v);

    tensor4* christ_3 = christoffel_symbols(metric_type, x_2, params);

    tensor4* input_k3_v[] = {christ_3, v_2, v_2};

    tensor4* minus_k3_v = tensor4_mult(input_k3_v, "mabab", 3);
    tensor4* k3_v = tensor4_scalar_mult(minus_k3_v, -1.0);

    tensor4* k3_x = tensor4_copy(v_2);


    tensor4_free(h2_k2_x);
    tensor4_free(h2_k2_v);
    tensor4_free(x_2);
    tensor4_free(v_2);
    tensor4_free(christ_3);
    tensor4_free(minus_k3_v);



    // k4:
    tensor4* h_k3_x = tensor4_scalar_mult(k3_x, step_size);
    tensor4* h_k3_v = tensor4_scalar_mult(k3_v, step_size);

    tensor4* x_3 = tensor4_add(x_0, h_k3_x);
    tensor4* v_3 = tensor4_add(v_0, h_k3_v);

    tensor4* christ_4 = christoffel_symbols(metric_type, x_3, params);

    tensor4* input_k4_v[] = {christ_4, v_3, v_3};

    tensor4* minus_k4_v = tensor4_mult(input_k4_v, "mabab", 3);
    tensor4* k4_v = tensor4_scalar_mult(minus_k4_v, -1.0);

    tensor4* k4_x = tensor4_copy(v_3);

    tensor4_free(h_k3_x);
    tensor4_free(h_k3_v);
    tensor4_free(x_3);
    tensor4_free(v_3);
    tensor4_free(christ_4);
    tensor4_free(minus_k4_v);



    tensor4* _2k2_v = tensor4_scalar_mult(k2_v, 2.0);
    tensor4* _2k2_x = tensor4_scalar_mult(k2_x, 2.0);
    tensor4* _2k3_v = tensor4_scalar_mult(k3_v, 2.0);
    tensor4* _2k3_x = tensor4_scalar_mult(k3_x, 2.0);


    tensor4* phi_v_12 = tensor4_add(k1_v, _2k2_v);
    tensor4* phi_v_123 = tensor4_add(phi_v_12, _2k3_v);
    tensor4* phi_v_1234 = tensor4_add(phi_v_123, k4_v);
    tensor4* h_phi_v = tensor4_scalar_mult(phi_v_1234, step_size/6.0);

    tensor4* phi_x_12 = tensor4_add(k1_x, _2k2_x);
    tensor4* phi_x_123 = tensor4_add(phi_x_12, _2k3_x);
    tensor4* phi_x_1234 = tensor4_add(phi_x_123, k4_x);
    tensor4* h_phi_x = tensor4_scalar_mult(phi_x_1234, step_size/6.0);

    tensor4_free(k1_v);
    tensor4_free(k1_x);
    tensor4_free(k2_v);
    tensor4_free(k2_x);
    tensor4_free(k3_v);
    tensor4_free(k3_x);
    tensor4_free(k4_v);
    tensor4_free(k4_x);
    tensor4_free(_2k2_v);
    tensor4_free(_2k2_x);
    tensor4_free(_2k3_v);
    tensor4_free(_2k3_x);



    tensor4* v_4 = tensor4_add(v_0, h_phi_v);
    tensor4* x_4 = tensor4_add(x_0, h_phi_x);

    tensor4** pp_tens_out = malloc(2 * sizeof(tensor4*));
    pp_tens_out[0] = x_4;
    pp_tens_out[1] = v_4;


    tensor4_free(phi_v_12);
    tensor4_free(phi_v_123);
    tensor4_free(phi_v_1234);
    tensor4_free(h_phi_v);
    tensor4_free(phi_x_12);
    tensor4_free(phi_x_123);
    tensor4_free(phi_x_1234);
    tensor4_free(h_phi_x);

    return pp_tens_out;
}
