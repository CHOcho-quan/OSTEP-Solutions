#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

int main() {
    int x = 10;
    pid_t p = fork();
    if (p < 0) {
        std::cout << "Fork failed\n";
        exit(-1);
    } else if (p == 0) {
        // child
        x = -1;
        std::cout << getpid() << " process x: " << x << '\n';
    } else {
        x = -2;
        std::cout << getpid() << " process x: " << x << '\n';
        wait(nullptr);
    }
}
