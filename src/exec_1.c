/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:11:28 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/22 01:11:20 by ergrigor         ###   ########.fr       */
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
	int	i;
	struct stat _path;

	i = 0;
	stat(cmd, &_path);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			break ;
		i++;
		if (cmd[i] == '\0' && !flag)
			return (0);
	}
	if (S_ISDIR(_path.st_mode) == 1)
	{
		int	fd = open(cmd, O_WRONLY, 0644);
		fprintf(stderr, "Gago: %s: %s\n", cmd, strerror(errno));
		return (set_status(126));
	}
	else if (access(cmd, X_OK | R_OK) == 0)
		return (1);
	// else
	// {
	// 	printf("%s\n", strerror(errno));
	// 	return (2);
	// }
	return (0);
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
		// dup2(S)
		printf("minishell: %s: command not found\n", cmd);
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

void	_execute(t_element *ptr)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (is_builtin(ptr->command->cmd) == 0)
		printf ("run_builtin(ptr->command)\n");
	else
	{
		pid = fork();
		if (pid == 0)
		{
			path = get_abs_path(get_paths(), ptr->command->cmd);
			if (execve(path, ptr->command->args, g_lobal->real_env) == -1)
			{
				set_status(127);
				exit(127);
			}
			exit(0);
		}
		else
			hd_wait(&status, &pid);
	}
}

void	single_execution(t_element *ptr)
{
	if (!ptr->command->args || !ptr->command->args[0]
		|| !ptr->command->args[0][0])
		return ;
	dup2(ptr->command->in, STDIN_FILENO);
	dup2(ptr->command->out, STDOUT_FILENO);
	_execute(ptr);
	dup2(g_lobal->all_fd[0], STDIN_FILENO);
	dup2(g_lobal->all_fd[1], STDOUT_FILENO);
	close(g_lobal->all_fd[0]);
	close(g_lobal->all_fd[1]);
	close(g_lobal->all_fd[2]);
	makefd();
}

void	execution(void)
{
	t_element	*ptr;

	ptr = g_lobal->elem;
	if (!ptr->next)
	{
		single_execution(ptr);
	}
	// else
	// 	pipe_execution(elem);
}