#include <math.h>

int array_index_from_index_array(int* indices, int num) {
    int out_index = 0;
    for (int i = 0; i < num; i++) {
        out_index += indices[i] * (int) pow(4.0, (double) i);
    }
    return out_index;
}
