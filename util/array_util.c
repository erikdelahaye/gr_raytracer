#include <math.h>

int array_index_from_index_array(int* indices, int num, int* p_out_index) {
    *p_out_index = 0;
    for (int i = 0; i < num; i++) {
        *p_out_index += indices[i] * (int) pow(4.0, (double) i);
    }
    return 0;
}
