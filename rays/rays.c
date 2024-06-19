#include "rays.h"

int* cast_ray(tensor4* x_0, tensor4* v_0, enum Evolvers evolver, double* evolver_params, object* objects, enum Metrics metric_type, double* metric_params) {
    tensor4* x_new;
    tensor4* v_new;

    int terminated = 0;

    while (!terminated) {
        switch (evolver) {
            case RK4:
                tensor4** step = evolvers_rk4(x_0, v_0, evolver_params[0], metric_type, metric_params);
                x_new = step[0];
                v_new = step[1];
                
                // TODO: check collision

                x_0 = x_new;
                v_0 = v_new;
                break;

            default:
                fprintf(stderr, "Error: Evolver not recognised\n");
                terminated = 1;
                break;

        } 
    }


    // TODO: determine rgb to be used for pixel
}
