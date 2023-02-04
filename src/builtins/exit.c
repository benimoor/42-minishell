#include "main.h"

void	exit_error_log(char *command)
{
	ft_putstr_fd(get_val_value("PS1"), 2);
	ft_putstr_fd(": exit: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
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

void	do_exit_2(char *command)
{
	int	n;
	// int				num;

	// num = ft_atoi(command);
	n = ft_atoi(command);
	if (n > 255)
		n = n % 256;
	else if (n < 0)
	{
		while (n < 0)
			n = n + 256;
	}
	set_status(n);
	ft_putstr_fd("exit\n", 1);
	exit (0);
}

void	do_exit(char *command)
{
	if (!exit_parsing(command) || ft_strlen(command) >= 20)
	{
		set_status(2);
		ft_putstr_fd("exit\n", 1);
		exit_error_log(command);
		exit (0);
	}
	else if (ft_strlen(command) >= 20)
	{
		set_status(2);
		ft_putstr_fd("exit\n", 1);
		exit_error_log(command);
		exit(0);
	}
	else
		do_exit_2(command);
}

int	built_in_exit(t_element *elem)
{
	char	**command;

	command = elem->command->args;
	if (!command[1])
	{
		set_status(0);
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else if (command[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd(get_val_value("PS1"), 2);
		ft_putstr_fd(": exit: too many arguments\n", 2);
		set_status(1);
		exit (0);
	}
	else if (command[1])
		do_exit(command[1]);
	return (0);
}
