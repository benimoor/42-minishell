/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:51:09 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/27 00:11:43 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_in_file(char *line, int fd, int flag, size_t len)
{
	char	*new_line;

	if (flag == 1 || (flag == 0 && no_var(line, ft_strlen(line)) == 0))
		write(fd, line, len);
	else
	{
		new_line = remake_var_line(line, ft_strlen(line));
		write(fd, new_line, ft_strlen(new_line));
		free(new_line);
	}
}

void	hd_wait(int *status, pid_t *pid)
{
	waitpid(*pid, status, 0);
	if (WIFEXITED(*status))
		set_status(WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
	{
		write(1, "\n", 1);
		set_status(WTERMSIG(*status) + 128);
	}
}

int	get_status(void)
{
	t_env	*ptr;

	ptr = g_lobal->env;
	while (ptr)
	{
		if (ft_strcmp(ptr->val_name, "?") == 0)
			return (ft_atoi(ptr->val_value));
		ptr = ptr->next;
	}
	return (-1);
}
