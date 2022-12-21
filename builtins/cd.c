#include "../Includes/main.h"

int main(int argc, char **argv, char **env)
{
    if (argc < 2)
        chdir("~/");
    else if (argc > 3)
    {
        printf("cd: too many arguments\n");
        exit(2);
    }
    // int fd = open("./README.md", O_RDONLY);
    // printf("%d\n", fd);
    // //Printing the now current working directory
    // printf("%s\n",getcwd(s,100));
    // nneed to continue
    return 0;
}