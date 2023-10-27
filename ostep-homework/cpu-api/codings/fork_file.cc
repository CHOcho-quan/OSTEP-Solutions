#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>

int main() {
    int fd = open("./dummy.txt", O_CREAT | O_RDWR, 0777);
    pid_t p = fork();
    if (p < 0) {
        std::cout << "Fork failed\n";
        exit(-1);
    } else if (p == 0) {
        // child
        char buf = 's';
        if (write(fd, &buf, 1) == -1) std::cout << "Write failed for child\n";
        std::cout << getpid() << " process x: " << fd << '\n';
    } else {
        char buf = 'p';
        if (write(fd, &buf, 1) == -1) std::cout << "Write failed for parent\n";
        std::cout << getpid() << " process x: " << fd << '\n';
    }
}
