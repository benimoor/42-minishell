/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:44:40 by ergrigor          #+#    #+#             */
/*   Updated: 2023/02/03 10:36:20 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	norm_free_elem(t_element *start, t_element *next, t_element	**elem)
{
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

void	free_elem(t_element	**elem)
{
	t_element	*start;
	t_element	*next;

	while (*elem)
	{
		start = *elem;
		next = *elem;
		norm_free_elem(start, next, elem);
	}
	free(*elem);
}

void	set__env(void)
{
	t_element	*ptr;
	t_env		*envptr;
	int			i;

	i = 0;
	envptr = g_lobal->env;
	ptr = g_lobal->elem;
	while (ptr && ptr->next)
		ptr = ptr->next;
	if (ptr && ptr->command && ptr->command->args)
	{
		while (ptr->command->args[i])
			i++;
		add_env_value("_", ptr->command->args[i - 1], 0, &envptr);
	}
}

void	destroy_struct(void)
{
	free_token(&(g_lobal)->tokens);
	set__env();
	free_elem(&(g_lobal)->elem);
	close_fd();
	g_lobal->hd_sig = 0;
	printf("\033[0m");
}
