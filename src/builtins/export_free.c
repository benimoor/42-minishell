/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:49:03 by ergrigor          #+#    #+#             */
/*   Updated: 2023/02/06 18:49:04 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	free_exported_env(t_env **head)
{
	t_env	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}

int	export_free(t_env *new_node, char *name)
{
	free(new_node);
	free(name);
	return (1);
}
