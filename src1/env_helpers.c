/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 18:34:26 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 17:37:08 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

char	*get_val_name(char *env_line)
{
	int		i;
	char	*value;

	i = 0;
	while (env_line[i] != '=' && env_line[i] != '\0')
		i++;
	value = malloc(i + 1);
	if (!value)
		return (NULL);
	value[i] = '\0';
	i--;
	while (i >= 0)
	{
		value[i] = env_line[i];
		i--;
	}
	return (value);
}

char	*get_val(char *env_line)
{
	int		i;
	int		tmp;
	char	*value;

	i = 0;
	while (env_line[i] != '=')
		i++;
	tmp = i;
	i++;
	while (env_line[i] != '\0')
		i++;
	value = malloc(i - tmp);
	if (!value)
		return (NULL);
	while (i > tmp)
	{
		value[i - tmp - 1] = env_line[i];
		i--;
	}
	return (value);
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
	// printf("val-value[%s]\n", tmp->val_value);
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

void	add_hidden_values(t_env **env_new)
{
	char	*tmp;

	tmp = get_pid();
	add_env_value("$", tmp, 1, env_new);
	free(tmp);
	add_env_value("?", "0", 1, env_new);
	add_env_value("0", "minishell", 1, env_new);
	check_shlvl(env_new);
}

//get the linked list from char** ENV
t_env	*pars_env(char **env)
{
	t_env	*list_env;
	t_env	*env_start;
	int		index;

	list_env = ft_calloc(sizeof(t_env), 1);
	env_start = list_env;
	index = 0;
	while (env[index] != NULL)
	{
		list_env->val_name = get_val_name(env[index]);
		list_env->val_value = get_val(env[index]);
		if (env[index + 1] == NULL)
		{
			list_env->next = NULL;
			break ;
		}
		list_env->next = malloc(sizeof(t_env));
		if (!list_env->next)
			return (NULL);
		list_env->next->prev = list_env;
		list_env = list_env->next;
		index++;
	}
	add_hidden_values(&env_start);
	return (env_start);
}
