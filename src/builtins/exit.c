#include "main.h"

void	exit_error_log(char *command)
{
	ft_putstr_fd("Say - Hello myalmo >: exit: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	set_shell_status(int n)
{
	t_env	*sh_s;
	char	*num;

	num = ft_itoa(n);
	sh_s = env_exist(g_lobal->env, "?");
	if (sh_s != NULL)
		sh_s->val_value = num;
	else
	{
		sh_s = malloc(sizeof(t_env));
		sh_s->val_name = "?";
		sh_s->val_value = num;
		sh_s->hidden = 1;
		sh_s->next = NULL;
		ft_lstadd_back_env(&g_lobal->env, sh_s);
	}
	return (0);
}

int	exit_parsing(char *command)
{
	int	i;

	i = 0;
	if (command[0] == '+' || command[0] == '-')
		i++;
	while (command[i])
	{
		if (ft_isdigit(command[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	do_exit(char *command)
{
	unsigned int	n;
	int				num;

	if (!exit_parsing(command) || ft_strlen(command) >= 20)
	{
		set_shell_status(2);
		exit_error_log(command);
		return (0);
	}
	else if (ft_strlen(command) >= 20)
	{
		set_shell_status(2);
		exit_error_log(command);
		exit(0);
	}
	else
	{
		num = ft_atoi(command);
		n = num;
		if (n > 255)
			n = n % 256;
		set_shell_status(n);
		exit (0);
	}
	return (0);
}

int	built_in_exit(t_element *elem)
{
	char	**command;
	int		num;

	command = elem->command->args;
	if (!command[1])
	{
		set_shell_status(0);
		exit(0);
	}
	else if (command[2])
	{
		ft_putstr_fd("Say - Hello myalmo >: exit: too many arguments\n", 2);
		set_shell_status(1);
		return (0);
	}
	else if (command[1])
		do_exit(command[1]);
	return (0);
}
