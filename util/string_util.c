#include "string_util.h"

int remove_spaces(char* input) {
    int offset = 0, 
        i = 0;
    do {
        while (input[i+offset] == ' ') {
            offset++;
        }
        input[i] = input[i+offset];
        i++;
    } while (input[i+offset-1] != '\0');
}
