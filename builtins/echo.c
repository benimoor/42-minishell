#include "../Includes/main.h"

int mini_parser(char *echo_flag, int *flag)
{
    int i;

    i = 0;
    if (strcmp(echo_flag, "-n") == 0)
    {
        *flag = 0;
        return (1);
    }
    return (0);
}

int main(int argc, char *argv[])
{
    int flag_endl;

    flag_endl = 1;
    if (argv[1])
        argv += mini_parser(argv[1], &flag_endl);
    while (*++argv) {
        printf("%s", *argv);
        if (argv[1]) printf(" ");
    }
    if (flag_endl)
        printf("\n");
    return (0);
}