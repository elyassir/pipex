#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int id = fork();
    int i;
    int j = 0;

    if (id == 0)
        printf("Heello From One\n");
    else 
        i = 1;
    id = fork();
    if (id == 0)
        printf("Heello From Two\n ");
    else 
        i = 1;
    j = i + 5;
    //wait();
    for (; i < j; i++)
    {
        printf("%d ", i);
    }
    //printf("Hello World From Id: %d\n", id);
    return 0;
}
