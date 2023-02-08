/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:49:06 by ergrigor          #+#    #+#             */
/*   Updated: 2023/02/06 18:50:34 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	export_without_equal(char *name, t_env *new_node)
{
	new_node->val_name = get_val_name(name);
	new_node->val_value = NULL;
	new_node->hidden = 2;
	new_node->next = NULL;
	ft_lstadd_back_env(&g_lobal->env, new_node);
}

int	export_with_arg(char *command)
{
	t_env	*node;
	t_env	*new_node;
	char	*name;

	name = get_val_name(command);
	if (name[ft_strlen(name) - 1] == '+')
		name[ft_strlen(name) - 1] = '\0';
	node = env_exist(g_lobal->env, name);
	new_node = malloc(sizeof(t_env));
	if (command_parsing(command) == 0)
	{
		export_error_log(command);
		return (export_free(new_node, name));
	}
	if (ft_strchr(command, '=') != NULL)
	{
		if (!export_with_equal(name, command, new_node, node))
			return (export_free(new_node, name));
	}
	else
		if (!node)
			export_without_equal(name, new_node);
	return (0);
}

int	do_export(char **command, t_env	*head)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = NULL;
	if (!command[1])
	{
		tmp = head;
		tmp = sort_env(&tmp);
		print_exported_env(tmp);
	}
	else
	{
		while (command[++i])
		{
			if (export_with_arg(command[i]) == 1)
				return (set_status(1));
		}
	}
	if (tmp)
		free_exported_env(&tmp);
	return (set_status(0));
}

void	built_in_export(t_element *elem)
{
	char	**command;
	t_env	*head;
	t_env	*tmp;

	tmp = g_lobal->env;
	head = ft_lstnew_env(tmp->val_name, tmp->val_value, tmp->hidden);
	tmp = tmp->next;
	while (tmp)
	{
		ft_lstadd_back_env(&head, ft_lstnew_env(tmp->val_name,
				tmp->val_value, tmp->hidden));
		tmp = tmp->next;
	}
	command = elem->command->args;
	do_export(command, head);
}
