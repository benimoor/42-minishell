/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pars2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:45:50 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/27 00:03:29 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	add_hidden_values(t_env **env_new)
{
	char	*tmp;

	tmp = get_pid();
	add_env_value("$", tmp, 1, env_new);
	free(tmp);
	add_env_value("?", "0", 1, env_new);
	add_env_value("0", "KARGIN-shell", 1, env_new);
	check_shlvl(env_new);
}

void	add_env_value(char *name, char *val, int hidden, t_env **env_new)
{
	t_env	*ptr;
	t_env	*tmp;

	ptr = *env_new;
	while (ptr)
	{
		if (ft_strcmp(name, ptr->val_name) == 0)
		{
			free(ptr->val_value);
			ptr->val_value = ft_strdup(val);
			ptr->hidden = hidden;
			return ;
		}
		ptr = ptr->next;
	}
	tmp = ft_calloc(sizeof(t_env), 1);
	tmp->val_name = ft_strdup(name);
	tmp->val_value = ft_strdup(val);
	tmp->hidden = hidden;
	tmp->next = *env_new;
	(*env_new)->prev = tmp;
	*env_new = tmp;
}

char	*get_pid(void)
{
	char	*name;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exit(0);
	else
	{
		wait(&status);
		name = ft_itoa((int)pid - 1);
	}
	return (name);
}

void	check_shlvl(t_env **env)
{
	t_env	*ptr;
	int		tmp;

	ptr = *env;
	while (ptr)
	{
		if (ft_strcmp(ptr->val_name, "SHLVL") == 0)
		{
			tmp = ft_atoi(ptr->val_value);
			free(ptr->val_value);
			ptr->val_value = ft_itoa(tmp + 1);
			return ;
		}
		ptr = ptr->next;
	}
}
