#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    int id = fork();
    int i;
    int j = 0;

    if (id == 0)
        i = 6;
    else 
        i = 1;
    
    j = i + 5;
    //wait();
    //for (; i < j; i++)
    //{
        printf("%d ", i++);
        printf("%d ", i++);
        printf("%d ", i++);
        printf("%d ", i++);
        printf("%d ", i++);
        fflush(stdout);
    //}
    //printf("Hello World From Id: %d\n", id)++;
    return 0;
}
