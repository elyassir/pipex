#include "pipex.h"
char    *get_cmd_path(char **paths, char **av_2)
{
    char *path;
    av_2[0] = ft_strjoin("/", av_2[0], 1);
    while (*paths != NULL)
    {
        path = ft_strjoin(*paths, av_2[0], 0);
        if (access(path, F_OK | X_OK) == 0)
            break;
        paths++;
    }
    if (*paths == NULL)
        return (NULL);
    return path;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (b[i] != '\0' && a[i] != '\0' && b[i] == a[i])
		i++;
    if (b[i] != '\0' && a[i] != '\0' && b[i] != a[i])
        return (a[i] - b[i]);
    return (0);
}
#include <fcntl.h>
char **get_paths(char **envp)
{
    int i = 0;
    while (envp[i] != NULL && ft_strcmp(envp[i], "PATH") != 0 )
        i++;
    return (ft_split(*(envp  + i) + 5, ':'));
}
int main(int argc, char  * argv[], char  *envp[])
{
    if (argc != 5)
    {
        write(2, "5 Args\n", 7);
        return (0);
    }
    int fd[2];
    pipe(fd);
    int i = 0;
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0)
    {
        write(2, "infile: No such file or directory\n", 35);
        exit(0);
    }
    int fd2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0600);
            //O_TRUNC         truncate size to 0 Delets all the data in it
    if (fd1 < 0)
    {
        write(2, "Error in Outfile\n", 18);
        exit(0);
    }
    char **paths = get_paths(envp);// "/bin/ls";
    char **cmd1 = ft_split(argv[2], ' ');
    char *path = get_cmd_path(paths, cmd1);
    if (path == NULL)
    {
        write(2, "Command Not Found\n", 18);
        close(fd[0]);
        close(fd[1]);
        exit(1);
    }
    if (fork() == 0)
        get_cmd_child_1(path, cmd1, fd, fd1);
    char **cmd2 = ft_split(argv[3], ' ');
    path = get_cmd_path(paths, cmd2);
    wait(NULL);
    if (path == NULL)
    {
        write(2, "Command Not Found\n", 18);
        close(fd[0]);
        close(fd[1]);
        exit(1);
    }
    if (fork() == 0)
        get_cmd_child_2(path, cmd2, fd, fd2);

    close(fd[0]);
    close(fd[1]);
    wait(NULL);
    return 0;
}