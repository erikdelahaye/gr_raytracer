#ifndef OBJECTS_H_IMPORTED
#define OBJECTS_H_IMPORTED

#include "../tensors/tensor4.h"
#include "../vectors/vec3.h"

enum Objects {
    STAR,
    DISK
};

typedef struct {
    enum Objects type;
    vec3 position;
    double radius;
} object;

#endif
