#include "../Includes/main.h"

void    main(int argc, char **argv, char **env)
{
	char str[NAME_MAX];

    if (argc > 1)
    {
        printf("pwd: too many arguments\n");
        exit(1);
    }
	getcwd(str, NAME_MAX);
	if (!str)
		exit(0);
	printf("%s\n", str);
    exit(0);
}