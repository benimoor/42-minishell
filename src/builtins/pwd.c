/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:49:09 by ergrigor          #+#    #+#             */
/*   Updated: 2023/02/06 18:49:10 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	built_in_pwd(void)
{
	char	pwd[PATH_MAX];
	char	*pwd_ptr;

	getcwd(pwd, sizeof(pwd));
	pwd_ptr = ft_strdup(pwd);
	ft_putstr_fd(pwd_ptr, 1);
	ft_putstr_fd("\n", 1);
	free (pwd_ptr);
	set_status(0);
}
