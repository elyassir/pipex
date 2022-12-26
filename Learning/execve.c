#include <unistd.h>
// execute program
// int execve(const char *filename, char *const argv[], char *const envp[]):


// which ls => /bin/ls  (filename a binary executable)
// ./a.out -l -a => arguments (argv)

// argv => the first of these strings should contain the filename like "/bin/ls"
// execve ignore the first argument in argv => cause it seem like you enter ls -a -l ignore ( ls )

// envp and argv => both must be terminated by NULL pointer

#include <stdio.h>
int main(int argc, char  * argv[], char  *envp[])
{
    argv++;
    // while (*argv)
    // {
    //     printf("%s\n", *argv);
    //     argv++;
    // }
    int i = execve("/bin/ls", argv, NULL); // NULL or envp it will executed
    if ( i == -1)
        printf("Error \n");
        
    printf("Error %d\n %s%s%s", i, argv[0], argv[1], argv[2]); // does not exucute cause 
    // execve is success and all data are freeded

    return 0;
}
// return value => execve does not return on success , and the text, data, bss, and stack of the calling process are overwrittten 
