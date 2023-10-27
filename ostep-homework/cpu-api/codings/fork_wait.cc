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
        // This returns -1
        std::cout << "child wait return: " << wait(nullptr) << '\n';
    } else {
        x = -2;
        std::cout << getpid() << " process x: " << x << '\n';
        /* wait returns the pid of child */
        // std::cout << "parent wait return: " << wait(nullptr) << '\n';
        int status = 0;
        /* waitpid returns the pid of child */
        std::cout << "parent waitpid return: " << waitpid(p, &status, WCONTINUED) << '\n';
        std::cout << "waitpid status: " << status << '\n';
    }
}
