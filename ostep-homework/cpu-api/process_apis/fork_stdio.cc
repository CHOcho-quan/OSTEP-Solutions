#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

int main() {
    pid_t p = fork();
    if (p < 0) {
        std::cout << "Fork failed\n";
        exit(-1);
    } else if (p == 0) {
        // child
        close(STDOUT_FILENO);
        std::cout << getpid() << " child process'\n'";
    } else {
        wait(nullptr);
        std::cout << getpid() << " parent process\n";
    }
}
