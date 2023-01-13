/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:41:15 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/13 23:40:34 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

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
	while (i < global->fd_index)
		close(global->all_fd[i++]);
}

void	free_cmd(t_element **elem)
{
	int	i;
	t_element *ptr;

	ptr = *elem;
	i = 0;
	while (ptr->command && ptr->command->args && ptr->command->args[i])
		free(ptr->command->args[i++]);
	//printf("hasav1\n");
	if (ptr->command && ptr->command->args)
		free(ptr->command->args);
	free(ptr->command);
	free(*elem);
}

void	free_elem(t_element	**elem)
{
	t_element	*start;
	t_element	*next;

	while (*elem)
	{
		start = *elem;
		next = *elem;
		while (next->next)
		{
			start = next;
			next = next->next;
		}
		if (start == next)
		{
			printf("hasav\n");
			if ((*elem)->type == 1)
				free(*elem);
			else
				free_cmd(elem);
			*elem = NULL;
		}
		else
		{
			start->next = NULL;
			if (next->type == 1)
				free(next);
			else
				free_cmd(&next);
		}
	}
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

void	destroy_struct(void)
{
	free_token(&(global)->tokens);
	free_elem(&(global)->elem);
	close_fd();
}
