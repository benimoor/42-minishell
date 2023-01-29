#include "main.h"

void	run_builtin(t_element **ptr)
{
	t_element	*elem;
	int			i;

	elem = *ptr;
	if (ft_strcmp(elem->command->args[0], "echo") == 0)
		set_status(built_in_echo(elem));
	else if (ft_strcmp(elem->command->args[0], "cd") == 0)
		built_in_cd(elem);
	else if (ft_strcmp(elem->command->args[0], "pwd") == 0)
		built_in_pwd(elem);
	else if (ft_strcmp(elem->command->args[0], "env") == 0)
		print_env(g_lobal->real_env);
	else if (ft_strcmp(elem->command->args[0], "export") == 0)
		built_in_export(elem);
	else if (ft_strcmp(elem->command->args[0], "unset") == 0)
		built_in_unset(elem);
	else if (ft_strcmp(elem->command->args[0], "exit") == 0)
		built_in_exit(elem);
	elem = elem->next;
	*ptr = elem;
}
