#include <stdbool.h>

int mx_isspace(char c) {
    if (c == 32)
        return 1;
    else
        return 0;
}
