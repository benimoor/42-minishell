/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_charptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:00:36 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/27 00:00:50 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_env_var_count(t_env *l_env)
{
	int	l;

	l = 0;
	while (l_env->next)
	{
		if(l_env->hidden != 1)
			l++;
		l_env = l_env->next;
	}
	return (l);
}


char	*get_line_env(t_env *l_env)
{
	char	*line;
	int		i;
	int		j;
	int		name;
	int		value;

	name = ft_strlen(l_env->val_name);
	value = ft_strlen(l_env->val_value);
	i = -1;
	line = ft_calloc((name + value + 2), sizeof(char));
	while (++i < name)
		line[i] = l_env->val_name[i];
	line[i] = '=';
	j = 0;
	while (j < value)
		line[++i] = l_env->val_value[j++];
	return (line);
}

// get the char ** from linked list 
char	**get_arr_env(t_env *l_env)
{
	char	**env;
	int		l;
	int		i;

	l = get_env_var_count(l_env);
	env = ft_calloc((l + 1), sizeof(char *));
	i = 0;
	while (i < l)
	{
		if (l_env->hidden != 1)
		{
			env[i] = get_line_env(l_env);
			i++;
		}
		l_env = l_env->next;
	}
	return (env);
}