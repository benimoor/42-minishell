/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:48:51 by ergrigor          #+#    #+#             */
/*   Updated: 2023/02/06 20:10:09 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_char(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	check_long_num(char *str, int j, int status)
{
	int				i;

	i = -1;
	if (check_char(str) == 1)
	{
		ft_putstr_fd(get_val_value("PS1: "), 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": exit: numeric argument required\n", 2);
		exit(255);
	}	
	if (ft_strlen(str) >= 19
		&& ((ft_strcmp(str, "9223372036854775807") <= 0) || \
	(j == 1 && ft_strcmp(str, "9223372036854775808") <= 0)))
	{
		ft_putstr_fd(get_val_value("PS1: "), 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": exit: numeric argument required\n", 2);
		exit(255);
	}
	else
	{
		exit (status);
	}
	return (0);
}

void	do_exit(char *command)
{
	unsigned char	gago;
	int				k;

	k = 0;
	gago = ft_atoi(command);
	while (*command && *command == ' ')
		*command += 1;
	if (*command == '-' || *command == '+')
	{
		if (*command == '-')
			k = 1;
		*command += 1;
	}
	check_long_num(command, k, gago);
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
		return (set_status(1));
	}
	else if (command[1])
		do_exit(command[1]);
	return (0);
}
