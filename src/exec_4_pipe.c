/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_4_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:01:48 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/31 01:36:27 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	do_pipe_execute_child_pipes(t_element *ptr,
		int (*pipes)[2], int pip_count, int i)
{
	if (i == 0)
	{
		ptr->command->out = pipe_or_redir_out(ptr->command, pipes, i);
		dup2(ptr->command->out, STDOUT_FILENO);
	}
	else if (i > 0 && i < pip_count)
	{
		ptr->command->out = pipe_or_redir_out(ptr->command, pipes, i);
		ptr->command->in = pipe_or_redir_input(ptr->command, pipes, i);
		dup2(ptr->command->in, STDIN_FILENO);
		dup2(ptr->command->out, STDOUT_FILENO);
	}
	else
	{
		ptr->command->in = pipe_or_redir_input(ptr->command, pipes, i);
		dup2(ptr->command->in, STDIN_FILENO);
		dup2(ptr->command->out, STDOUT_FILENO);
	}
	close_all_pipes(pipes, pip_count);
}

void	do_pipe_execute_child_execution(t_element *ptr,
		int (*pipes)[2], int pip_count)
{
	if (ptr->command->cmd[0] == '\0')
	{
		print_error(ptr->command->cmd, "command not found");
		exit(set_status(127));
	}
	if (is_builtin(ptr->command->cmd) == 0)
		run_builtin(&ptr);
	else if (execve(get_abs_path(get_paths(), ptr->command->cmd),
			ptr->command->args, g_lobal->real_env) == -1)
	{
		close_all_pipes(pipes, pip_count);
		exit(set_status(127));
	}
}

void	do_pipe_execute_child(t_element *ptr,
		int (*pipes)[2], int pip_count, int i)
{
	if (ptr->command->in == -1 || ptr->command->out == -1)
	{
		print_error(ptr->command->cmd, "No such file or directory");
		exit(set_status(1));
	}
	dup2(ptr->command->in, STDIN_FILENO);
	dup2(ptr->command->out, STDOUT_FILENO);
	do_pipe_execute_child_pipes(ptr, pipes, pip_count, i);
	do_pipe_execute_child_execution(ptr, pipes, pip_count);
	dup2(ptr->command->in, STDIN_FILENO);
}

int	do_pipe_execute(t_element *ptr, int (*pipes)[2], int pip_count)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (ptr != NULL)
	{
		if (!ptr->command->args)
			ptr = ptr->next;
		pid = fork();
		if (pid == 0)
			do_pipe_execute_child(ptr, pipes, pip_count, i);
		i++;
		ptr = ptr->next;
	}
	close_all_pipes(pipes, pip_count);
	return (i);
}
