/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:41:04 by ergrigor          #+#    #+#             */
/*   Updated: 2023/02/01 03:23:17 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	execute_cmd(t_element *ptr)
{
	pid_t	pid;
	int		status;

	if (set_status(is_directory(ptr->command->cmd)) >= 125)
	{
		if (get_status() == 125)
			print_error(ptr->command->cmd, "\nNo such file or directory\n");
		else
			print_error(ptr->command->cmd, "\nIs a directory\n");
		return ;
	}
	pid = fork();
	if (pid == 0)
	{	
		signal(SIGINT, handler);
		if (execve(get_abs_path(get_paths(), ptr->command->cmd),
				ptr->command->args, get_arr_env(g_lobal->env)) == -1)
		{
			exit(set_status(127));
		}
	}
	else
		hd_wait(&status, &pid);
}

void	_execute(t_element *ptr)
{
	if (!ptr->command || !ptr->command->args || !ptr->command->args[0])
		return ;
	if (ptr->command->cmd[0] == '\0')
	{
		print_error(ptr->command->cmd, "command not found");
		set_status(127);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, handle_quit);
	if (ptr->command->in == -1 || ptr->command->out == -1)
		set_status(1);
	if (ptr->command->in == -1)
		print_error(ptr->command->cmd, "No such file or directory");
	else if (ptr->command->out == -1)
		print_error(ptr->command->cmd, "Is a directory");
	else if (is_builtin(ptr->command->cmd) == 0)
		run_builtin(&ptr);
	else
		execute_cmd(ptr);
}

void	single_execution(t_element *ptr)
{
	if (!ptr->command && !ptr->command->args)
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
		single_execution(ptr);
	else
		pipe_execution(ptr);
}

// void	close_all_elem_fd(void)
// {
// 	t_element *elem;

// 	elem = g_lobal->elem;
// 	while(elem)
// 	{
// 		if(elem->command)
// 		{
// 			close(elem->command->in);
// 			close(elem->command->out);
// 			close(elem->command->err);
// 		}
// 		elem = elem->next;
// 	}
// }

void	pipe_execution(t_element *ptr)
{
	int	(*pipes)[2];
	int	pip_count;
	int	i;
	int	counter;
	int	status;

	pip_count = pipe_count(ptr) - 1;
	pipes = malloc(sizeof(*pipes) * pip_count);
	i = -1;
	while (++i < pip_count)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe failed");
			exit(1);
		}
	}
	i = -1;
	counter = do_pipe_execute(ptr, pipes, pip_count);
	while (++i < counter)
		wait(&status);
	close_all_pipes(pipes, pip_count);
	free(pipes);
	set_status(WEXITSTATUS(status));
}
