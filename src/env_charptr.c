/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_charptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:00:36 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 20:03:34 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_env_var_count(t_env *l_env)
{
	int	l;

	l = 0;
	while (l_env->next)
	{
		l++;
		l_env = l_env->next;
	}
	return (l + 1);
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
	i = 0;
	line = malloc(name + value + 2);
	while (i < name)
	{
		line[i] = l_env->val_name[i];
		i++;
	}
	line[i] = '=';
	j = 0;
	while (j < value)
		line[++i] = l_env->val_value[++j];
	line[i] = '\0';
	return (line);
}

// get the char ** from linked list 
char	**get_arr_env(t_env *l_env)
{
	char	**env;
	int		l;
	int		i;

	l = get_env_var_count(l_env);
	env = (char **)malloc((1 + l) * sizeof(char *));
	i = 0;
	while (i < l)
	{
		env[i] = get_line_env(l_env);
		l_env = l_env->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}