
#include "../Includes/main.h"

int main(int argc, char *argv[], char * envp[])
{
    int i;

    i = 0;
    if (argc != 1)
    {
        printf("env: invalid option '%s'\n", argv[1]);
        printf("our env have not options\n");
        return (1);
    }
    while (envp[i])
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return 0;
}
