#include <unistd.h>
#include <stdio.h>

char		**ft_split(char const *s, char c);
int main(int argc, char  * argv[], char  *envp[])
{

    int i = 0;

    char **av;

    if (fork() == 0)
    {
        av = ft_split(argv[2], ' ');
        execve(av[0], av, envp);
    }

    if (fork() == 0)
    {
        av = ft_split(argv[3], ' ');
        execve(av[0], av, envp);
    }

    return 0;
}