/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:39:01 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/11 19:42:54 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

int	set_status(int status)
{
	t_env	*ptr;

	ptr = global->env;
	while (ptr && ptr->val_name[0] != '?')
		ptr = ptr->next;
	free(ptr->val_value);
	ptr->val_value = ft_itoa(status);
	return (0);
}
