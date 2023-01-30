/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:40:40 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/31 00:19:35 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_chardbp(char ***group)
{
	int	i;

	i = -1;
	if (group || *group)
	{
		while ((*group)[++i] != NULL)
			free((*group)[i]);
		free(*group);
		*group = 0x0;
	}
}

void	close_fd(void)
{
	int	i;

	i = 3;
	while (i < g_lobal->fd_index)
		close(g_lobal->all_fd[i++]);
}

void	free_cmd(t_element **elem)
{
	int			i;
	t_element	*ptr;

	ptr = *elem;
	i = 0;
	while (ptr->command && ptr->command->args && ptr->command->args[i])
		free(ptr->command->args[i++]);
	if (ptr->command && ptr->command->args)
		free(ptr->command->args);
	free(ptr->command);
	free(*elem);
}

void	free_token(t_token	**token)
{
	t_token	*start;
	t_token	*next;

	while (*token)
	{
		start = *token;
		next = *token;
		while (next->next)
		{
			start = next;
			next = next->next;
		}
		if (start == next)
		{
			free(*token);
			*token = NULL;
		}
		else
		{
			start->next = NULL;
			free(next);
		}
	}
	free(*token);
}
