/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:11:28 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/31 01:49:29 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

char	**get_paths(void)
{
	t_env	*ptr;

	ptr = g_lobal->env;
	while (ptr)
	{
		if (ft_strcmp(ptr->val_name, "PATH") == 0)
			return (ft_split(ptr->val_value, ':'));
		ptr = ptr->next;
	}
	return (NULL);
}

int	is_directory(char *cmd, int flag)
{
	int			i;
	struct stat	_path;

	i = 0;
	stat(cmd, &_path);
	if (*cmd == '\0')
		return (set_status(127));
	if (access(cmd, F_OK | X_OK) == 0)
	{
		return (set_status(126));
	}
	if (S_ISDIR(_path.st_mode) == 1)
	{
		return (set_status(126));
	}
	while (cmd[i])
	{
		if (cmd[i] == '/')
			break ;
		i++;
		if (cmd[i] == '\0' && !flag && i != 1)
			return (1);
	}
	return (set_status(127));
}

char	*get_abs_path(char **paths, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	if (access(cmd, X_OK | R_OK) == 0)
		return (cmd);
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		temp = ft_strjoin(temp, cmd);
		if (access(temp, X_OK | R_OK) == 0)
			break ;
		free (temp);
		i++;
	}
	if (access(temp, X_OK | R_OK) == 0)
		return (temp);
	else
	{
		printf("%s : %s: command not found\n", get_val_value("PS1"), cmd);
	}
	return (NULL);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	else
		return (1);
}

void	print_error(char *cmd, char *error)
{
	ft_putstr_fd(get_val_value("PS1"), 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}
