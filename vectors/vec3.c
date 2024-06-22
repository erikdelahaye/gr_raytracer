#include "vec3.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double vec3_scal_prod(vec3* x, vec3* y) {
    if (x->coordsys == y->coordsys) {
        switch (x->coordsys) {
            case CARTESIAN:
                return vec3_scal_prod_cartesian(x, y);
            case SPHERICAL:
                return vec3_scal_prod_spherical(x, y);
            default:
                fprintf(stderr, "Coordsys not recognised\n");
                return 0;
        }
    } else {
        vec3* x_cart = vec3_to_cartesian(x);
        vec3* y_cart = vec3_to_cartesian(y);
        double out = vec3_scal_prod_cartesian(x_cart, y_cart);
        free(x_cart);
        free(y_cart);
        return out;
    }
}

vec3* vec3_mult(vec3* x, double a) {
    vec3* out = malloc(sizeof(vec3));
    switch (x->coordsys) {
        case CARTESIAN:
            out->coordsys = CARTESIAN;
            out->x1 = x->x1 * a;
            out->x2 = x->x2 * a;
            out->x3 = x->x3 * a;
            return out;
        case SPHERICAL:
            out->coordsys = SPHERICAL;
            out->x1 = x->x1 * a;
            out->x2 = x->x2;
            out->x3 = x->x3;
            return out;
        default:
            fprintf(stderr, "Coordsys not recognised\n");
            free(out);
            return NULL;
    }
}

vec3* vec3_copy(vec3* x) {
    vec3* out = malloc(sizeof(vec3));
    out->coordsys = x->coordsys;
    out->x1 = x->x1;
    out->x2 = x->x2;
    out->x3 = x->x3;
    return out;
}

vec3* vec3_normalise(vec3* x) {
    double one_over_norm = 1/vec3_abs(x);

    vec3* out = malloc(sizeof(vec3));
    out->coordsys = x->coordsys;
    switch (x->coordsys) {
        case CARTESIAN:
            out->x1 = x->x1 * one_over_norm;
            out->x2 = x->x2 * one_over_norm;
            out->x3 = x->x3 * one_over_norm;
            break;
        case SPHERICAL:
            out->x1 = x->x1 * one_over_norm;
            out->x2 = x->x2;
            out->x3 = x->x3;
            break;
        default:
            fprintf(stderr, "Coordsys not recognised\n");
            free(out);
            return NULL;
    }
    return out;
}

vec3* vec3_to_cartesian(vec3* x) {
    switch (x->coordsys) {
        case CARTESIAN:
            return vec3_copy(x);
        case SPHERICAL:
            vec3* out = malloc(sizeof(vec3));
            out->x1 = x->x1 * cos(x->x3) * sin(x->x2);
            out->x2 = x->x1 * sin(x->x3) * sin(x->x2);
            out->x3 = x->x1 * cos(x->x2);
            return out; 
        default:
            fprintf(stderr, "Coordsys not recognised\n");
            return NULL;
    }
}

double vec3_scal_prod_cartesian(vec3* x, vec3* y) {
    double out = x->x1 * y->x1 + x->x2 * y->x2 + x->x3 * y->x3;
    return out;
}

double vec3_scal_prod_spherical(vec3* x, vec3* y) {
    double out = x->x1 * y->x1 * (sin(x->x3) * sin(y->x3) * cos(x->x2 - y->x2) + cos(x->x3) * cos(y->x3));
    return out;
}

double vec3_abs(vec3* x) {
    double out;
    switch (x->coordsys) {
        case CARTESIAN:
            out = sqrt(vec3_scal_prod_cartesian(x, x));
            return out;
        case SPHERICAL:
            return abs(x->x1);
        default:
            fprintf(stderr, "Coordsys not recognised\n");
            return 0;
    }
}
