#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2, int a);
char		**ft_split(char const *s, char c);
void    get_cmd_child_1(char *path,char **av_2, int *fd, int infile);
void    get_cmd_child_2(char *path,char **av_2, int *fd, int outfile);
#endif