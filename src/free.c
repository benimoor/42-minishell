/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:41:15 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/13 21:56:01 by ergrigor         ###   ########.fr       */
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

	i = 0;
	if ((*elem)->command->args)
		free_chardbp(&(*elem)->command->args);
	free((*elem)->command);
	free(*elem);
}

void	free_elem(t_element	**elem)
{
	t_element	*ptr;

	ptr = *elem;
	if (ptr && ptr->next)
		free_elem(&(ptr)->next);
	if (ptr->type == 1)
		free(ptr);
	else
		free_cmd(&ptr);
}

void	free_token(t_token	**token)
{
	t_token	*ptr;
	int		count;

	count = 0;
	ptr = *token;
	while (ptr)
	{
		ptr = ptr->next;
		count++;
	}
	ptr = *token;
	while (ptr)
	{
		while (ptr && ptr->next)
			ptr = ptr->next;
		if (ptr)
			free(ptr);
		else
			break ;
		ptr = *token;
	}
}

void	destroy_struct(void)
{
	free_token(&(global)->tokens);
	free_elem(&(global)->elem);
	close_fd();
}
