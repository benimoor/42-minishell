/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:49:12 by ergrigor          #+#    #+#             */
/*   Updated: 2023/02/06 18:49:13 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

t_env	*get_prev_node(t_env *head, char *name)
{
	t_env	*ptr;
	t_env	*prev;

	ptr = head;
	prev = NULL;
	if (ft_strcmp(ptr->val_name, name) == 0)
		return (NULL);
	while (ptr)
	{
		if (ft_strcmp(ptr->val_name, name) == 0)
			return (prev);
		prev = ptr;
		ptr = ptr->next;
	}
	return (NULL);
}

int	do_unset(char *command)
{
	t_env	*node;
	t_env	*prev;

	node = env_exist(g_lobal->env, command);
	if (!node)
		return (0);
	prev = get_prev_node(g_lobal->env, command);
	if (prev != NULL)
		prev->next = node->next;
	else
		g_lobal->env = node->next;
	free(node);
	return (0);
}

int	built_in_unset(t_element *elem)
{
	char	**command;
	int		i;

	i = 0;
	command = elem->command->args;
	while (command[++i])
		do_unset(command[i]);
	set_status(0);
	return (0);
}
