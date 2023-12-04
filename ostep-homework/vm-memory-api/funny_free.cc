#include <stdio.h>
#include <unistd.h>

#include <iostream>

int main() {
    int* data = (int *) malloc(100 * sizeof(int));
    for (int i = 0; i < 100; ++i) data[i] = 0;

    std::cout << data[100] << '\n';

    free((void *) data[55]);

    return 0;
}
