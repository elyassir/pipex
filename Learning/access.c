#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
int    main()
{

    //printf("%d\n", access("/Users/yel-mass/Desktop/pipex/Learning/a.out", F_OK | X_OK));
    // File existe and can exucte
    int fd = open("acc", O_WRONLY);
    write(fd, "Writeee", 5);
    return 0;
}