#include "pipex.h"
#include <fcntl.h>
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
char **get_paths(char **envp)
{
    int i = 0;
    while (envp[i] != NULL && ft_strcmp(envp[i], "PATH") != 0 )
        i++;
    return (ft_split(*(envp  + i) + 5, ':'));
}
int main(int argc, char  * argv[], char  *envp[])
{
    int fd[2]; // for pipe
    int infile;    
    int outfile;
    char **paths;   // path=/bin:/local/bin....
    char    *path;  // ex : /bin/ls 
    char **cmd1;
    char **cmd2;
    char **cmd;

    if (argc >= 1)
    {
        pipe(fd);
        infile = open(argv[1], O_RDONLY);
        if (infile < 0)
            write(2, "infile: No such file or directory\n", 35);
        paths = get_paths(envp);// "/bin/ls";
        cmd1 = ft_split(argv[2], ' '); ///   ls  -a  -l
        path = get_cmd_path(paths, cmd1);
        if (path == NULL)
            write(2, "Command Not Found\n", 18);
        if (path != NULL && !(infile < 0) && fork() == 0)
            get_cmd_child_1(path, cmd1, fd, infile);
        close(fd[1]);
        wait(NULL);

        int i = 2;// 0->a. 1->in 2->cmd1 
        while (++i < argc - 2) // 5 -> 3 
        {

            int fd2[2];
            pipe(fd2);
            cmd = ft_split(argv[i], ' ');
            path = get_cmd_path(paths, cmd);
            if (path == NULL)
                write(2, "Command Not Found\n", 18);
            if (path != NULL && fork() == 0)
                get_cmd_child_2(path, cmd, fd, fd2);
            wait(NULL);
            *fd = *fd2;
            close(fd2[1]);
        }

        outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644); 
        if (outfile < 0) 
            exit(12);
        cmd2 = ft_split(argv[argc - 2], ' ');
        path = get_cmd_path(paths, cmd2);
        if (path == NULL)
            write(2, "Command Not Found\n", 18);
        if (path != NULL && !(outfile < 0) && fork() == 0 )
            get_cmd_child_3(path, cmd2, fd, outfile);

        close(fd[0]);
        close(fd[1]);
    }
    else
        write(2, "5 Args\n", 7); 
    return 0;
}