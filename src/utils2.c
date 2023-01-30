/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:48:25 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/30 08:08:49 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	no_var(char *line, size_t len)
{
	size_t	i;

	i = 0;
	while (line[i] && i < len)
	{
		if (line[i] == '$')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	hd_count_check(t_token *token)
{
	int		count;
	int		flag;
	t_token	*ptr;

	count = 0;
	ptr = token;
	while (ptr)
	{
		if (ptr && ptr->type == HERE_DOC)
		{
			if (ptr->next && ptr->next->type == SPACE_TK)
				ptr = ptr->next->next;
			else
				ptr = ptr->next;
			if (!ptr)
				return (count);
			else if (ptr->type == WORD)
			{
				count++;
				ptr = ptr->next;
			}
			else if (ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES)
			{
				flag = ptr->type;
				ptr = ptr->next;
				while (ptr && ptr->type != flag)
					ptr = ptr->next;
				if (!ptr)
					return (count);
				else
					count++;
				ptr = ptr->next;
			}
			else
				return (count);
		}
		else
			ptr = ptr->next;
	}
	return (count);
}

char	*get_env_value(t_env *env, char *str, int *i)
{
	char	*tmp;
	t_env	*ptr;
	int		j;
	int		a;

	a = *i + 1;
	j = a;
	ptr = env;
	if (ft_isdigit(str[a]) == 1 && str[a] != '0')
	{
		*i = a + 1;
		return (ft_strdup(""));
	}
	else if (str[a] == '$')
	{
		*i = a + 1;
		return (get_dollar());
	}
	while (str[j] && str[j] != ' ' && str[j] != '\0' && str[j] != '\''
		&& str[j] != '"' && str[j] != '\n' && str[j] != '$' && str[j] != '=' && str[j] != '\\' && str[j] != '/')
		j++;
	tmp = ft_substr(str, a, (j - (*i) - 1));
	*i = j;
	while (ptr)
	{
		if (ft_strncmp(ptr->val_name, tmp, ft_strlen(tmp)) == 0
			&& ft_strlen(ptr->val_name) == ft_strlen(tmp))
			break ;
		ptr = ptr->next;
	}
	if (ptr == NULL)
		return (free(tmp), ft_strdup(""));
	return (free(tmp), ft_strdup(ptr->val_value));
}

char	*get_val_value(char *key)
{
	t_env	*envv;

	envv = g_lobal->env;
	while (envv)
	{
		if (ft_strcmp(key, envv->val_name) == 0)
			return (envv->val_value);
		envv = envv->next;
	}
	return (NULL);
}
