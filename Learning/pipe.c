#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
int main (int argc, char* argv[]) {
    int fd[2];

    pipe(fd);

    int pid1 = fork();
    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        execlp("ls", "ls", "-a", "-l", NULL);
    }
    wait(NULL);

    int pid2 = fork();
    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        execlp("wc", "wc", "-l", NULL); 
    }
    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    return 0;
}