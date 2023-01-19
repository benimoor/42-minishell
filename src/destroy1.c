/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:44:40 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 18:44:50 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

void	destroy_struct(void)
{
	free_token(&(global)->tokens);
	free_elem(&(global)->elem);
	close_fd();
}
