#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        std::cerr << "Pipe Failed\n";
        return -1;
    }

    pid_t p1 = fork(), p2 = fork();
    if (p1 < 0 || p2 < 0) {
        std::cout << "Fork failed\n";
        exit(-1);
    } else if (p1 == 0) {
        // child p1
        std::cout << getpid() << " child1 process\n";
        char buf = '1';
        write(fd[1], &buf, 1);
    } else if (p2 == 0) {
        // child p2
        std::cout << getpid() << " child2 process\n";
        sleep(1);
        char buf;
        read(fd[0], &buf, 1);
        std::cout << "Reading from Pipe: " << buf << '\n';
    } else {
        // parent
        std::cout << getpid() << " parent process\n";
        int status;
        waitpid(p1, &status, WCONTINUED);
        waitpid(p2, &status, WCONTINUED);
    }
}
