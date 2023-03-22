/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 22:45:36 by ergrigor          #+#    #+#             */
/*   Updated: 2023/03/22 22:49:35 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	export_with_equal_part1(char *name, char *command_name, t_env *new_node)
{
	new_node->val_name = name;
	new_node->val_value = command_name;
	new_node->hidden = 0;
	new_node->next = NULL;
	ft_lstadd_back_env(&g_lobal->env, new_node);
}

void	export_with_equal_part2(t_env *node, char *command_name)
{
	node->val_value = ft_free_strjoin(node->val_value, command_name);
	if (command_name)
		free(command_name);
}

void	export_with_equal_part3(t_env *node, char *command_name)
{
	if (node->val_value)
		free(node->val_value);
	node->val_value = get_val(command_name);
	if (command_name)
		free(command_name);
}

int	export_with_equal(char *name, char *command, t_env *new_node, t_env *node)
{
	char	*command_name;

	command_name = get_val(command);
	if (ft_strcmp(command, "=") == 0)
	{
		export_error_log ("=");
		free(command_name);
		return (0);
	}
	if (!node)
	{
		export_with_equal_part1(name, command_name, new_node);
	}
	else if ((ft_strchr(command, '=') - 1)[0] == '+')
		export_with_equal_part2(node, command_name);
	else
		export_with_equal_part3(node, command_name);
	if (node)
		node->hidden = 0;
	return (1);
}
