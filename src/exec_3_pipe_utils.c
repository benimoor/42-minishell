/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_3_pipe_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:49:07 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/30 23:01:30 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	pipe_count(t_element *ptr)
{
	int			count;
	t_element	*pptr;

	count = 0;
	pptr = ptr;
	while (pptr)
	{
		count++;
		pptr = pptr->next;
	}
	return (count);
}

void	close_all_pipes(int pips[][2], int pip)
{
	int	a;

	a = -1;
	while (++a < pip)
	{
		close(pips[a][1]);
		close(pips[a][0]);
	}
}

int	pipe_or_redir_input(t_command *command, int (*pipes)[2], int i)
{
	if (command->in == g_lobal->all_fd[0] || command->in == 0)
		return (pipes[i - 1][0]);
	return (command->in);
}

int	pipe_or_redir_out(t_command *command, int (*pipes)[2], int i)
{
	if (command->out == g_lobal->all_fd[1] || command->out == 1)
		return (pipes[i][1]);
	return (command->out);
}
