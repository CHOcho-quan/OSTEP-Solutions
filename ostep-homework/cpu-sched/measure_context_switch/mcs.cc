#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sched.h>
#include <chrono>

#include <iostream>

int main() {
    int fd[2], fd2[2];
    if (pipe(fd) == -1) {
        std::cerr << "Pipe Failed\n";
        return -1;
    }
    if (pipe(fd2) == -1) {
        std::cerr << "Pipe Failed\n";
        return -1;
    }

    cpu_set_t my_set;        /* Define your cpu_set bit mask. */
    CPU_ZERO(&my_set);       /* Initialize it all to 0, i.e. no CPUs selected. */
    CPU_SET(1, &my_set);     /* set the bit that represents core 7. */

    pid_t p1 = fork();
    if (p1 == 0) {
        // child p1
        sched_setaffinity(0, sizeof(cpu_set_t), &my_set);
        std::cout << getpid() << " child1 process\n";
        char buf = '1';
        auto st = std::chrono::steady_clock::now();
        for (int i = 0; i < 10000; ++i) {
            write(fd[1], &buf, 1);
            read(fd2[0], &buf, 1);
        }
        auto en = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(en - st).count()
                  << " Milliseconds for 10000 process context switch\n";
    } else {
        // parent
        sched_setaffinity(0, sizeof(cpu_set_t), &my_set);
        std::cout << getpid() << " parent process\n";
        char buf = '1';
        for (int i = 0; i < 10000; ++i) {
            write(fd2[1], &buf, 1);
            read(fd[0], &buf, 1);
        }
    }
}
