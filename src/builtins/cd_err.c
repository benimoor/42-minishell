/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:48:38 by ergrigor          #+#    #+#             */
/*   Updated: 2023/02/06 18:48:39 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	print_cd_err(char *path)
{
	ft_putstr_fd(get_val_value("PS1"), 2);
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	set_status(1);
}

void	cd_many_arg_err(void)
{
	ft_putstr_fd(get_val_value("PS1"), 2);
	ft_putstr_fd("cd: too many arguments\n", 2);
	set_status(1);
}
