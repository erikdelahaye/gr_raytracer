#include "rays.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int cast_ray(tensor4* x_0, tensor4* v_0, int ray_index, enum Evolvers evolver, double* evolver_params, object* objects, int num_objects, enum Metrics metric_type, double* metric_params) {
    tensor4* x_new;
    tensor4* v_new;

    int terminated = 0;

    while (!terminated) {
        switch (evolver) {
            case RK4:
                tensor4** step = evolvers_rk4(x_0, v_0, evolver_params[0], metric_type, metric_params);
                x_new = step[0];
                v_new = step[1];
                
                // TODO

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

tensor4*** step_rays(tensor4*** originals, int num_rays, enum Evolvers evolver, double* evolver_params, enum Metrics metric_type, double* metric_params) {
    tensor4*** out = malloc(num_rays * sizeof(tensor4**));

    #pragma omp parallel for
    for (int i = 0; i < num_rays; i++) {
        switch (evolver) {
            case RK4:
                out[i] = evolvers_rk4(originals[i][0], originals[i][1], evolver_params[0], metric_type, metric_params);
                break;
            default:
                fprintf(stderr, "Evolver not recognised\n");
                break;
        }
    }

    return out;
}
