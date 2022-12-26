#include "pipex.h"

void    get_cmd_child_1(char *path,char **av_2, int *fd, int infile)
{
    dup2(fd[1], STDOUT_FILENO);
    dup2(infile, STDIN_FILENO);
    close(fd[0]);
    execve(path, av_2, NULL);
}
void    get_cmd_child_2(char *path,char **av_2, int *fd, int outfile)
{
    dup2(fd[0], STDIN_FILENO);
    dup2(outfile, STDOUT_FILENO);
    close(fd[1]);
    execve(path, av_2, NULL);
}