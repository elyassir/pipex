#include <unistd.h>
#include <stdio.h>
char		**ft_split(char const *s, char c);
int main(int argc, char  * argv[], char  *envp[])
{
    // while (*argv)
    // {
    //     printf("%s\n", *argv);
    //     argv++;
    // }
    int i = 0;
    int j;
    char **av;
    //write(1, "\n", 1);
    while (++i < argc)
    {
        if (fork() == 0)
        {
            av = ft_split(argv[i], ' ');
            execve(av[0], av, envp);
        }

    }

    return 0;
}