#include "pipex.h"
#include <fcntl.h>
void    get_cmd_child_1(char *path,char **av_2, int *fd, int infile)
{
    // int in = open("in", O_WRONLY | O_TRUNC);
    // dup2(in, STDOUT_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    dup2(infile, STDIN_FILENO);
    execve(path, av_2, NULL);
}
void    get_cmd_child_2(char *path,char **av_2, int *fd, int *fd2)
{

    dup2(fd[0], 0);
    dup2(fd2[1], 1);
    execve(path, av_2, NULL);
}

void    get_cmd_child_5(char *path,char **av_2, int *fd, int *fd2)
{

    dup2(fd[0], 0);
    //close(fd[1]);
    dup2(fd2[1], 1);
    execve(path, av_2, NULL);
}

void    get_cmd_child_3(char *path,char **av_2, int *fd, int outfile)
{
    //int out = open("out", O_RDONLY);
    dup2(fd[0], 0);
    //close(fd[1]);
    dup2(outfile, 1);
    execve(path, av_2, NULL);
}