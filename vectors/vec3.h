#ifndef VEC3_H_IMPORTED
#define VEC3_H_IMPORTED

enum Coordsys {
    CARTESIAN,
    SPHERICAL
};

typedef struct {
    enum Coordsys coordsys;
    double x1;
    double x2;
    double x3;
} vec3;

double vec3_scal_prod(vec3* x, vec3* y);

vec3* vec3_mult(vec3* x, double a);

vec3* vec3_copy(vec3* x);

vec3* vec3_normalise(vec3* x);

vec3* vec3_to_cartesian(vec3* x);

double vec3_scal_prod_cartesian(vec3* x, vec3* y);

double vec3_scal_prod_spherical(vec3* x, vec3* y);

double vec3_abs(vec3* x);

#endif
