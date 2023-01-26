/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:49:11 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/26 19:43:46 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	empty_line(char *line)
{
	int	i;

	i = 0;
	if (line == NULL || line[0] == '\0')
		return (1);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0' && line[i - 1] == ' ')
		return (2);
	return (0);
}

int	set_status(int status)
{
	t_env	*ptr;

	ptr = g_lobal->env;
	while (ptr && ptr->val_name && ptr->val_name[0] != '?')
		ptr = ptr->next;
	if (ptr && ptr->val_name && ptr->val_name[0] == '?')
	{	free(ptr->val_value);
		ptr->val_value = ft_itoa(status);
		return (status);
	}
	return (0);
}

char	*ft_free_strjoin(char *s1, char *s2)
{
	char		*new_str;
	size_t		f_index;
	size_t		s_index;

	if (!s1)
		return (ft_strdup(s2));
	new_str = malloc(sizeof (char)
			* (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new_str)
		return (NULL);
	f_index = 0;
	s_index = 0;
	if (s1)
		while (s1[f_index])
			new_str[s_index++] = s1[f_index++];
	f_index = 0;
	if (s2)
		while (s2[f_index])
			new_str[s_index++] = s2[f_index++];
	new_str[s_index] = '\0';
	if (s1)
		free(s1);
	return (new_str);
}

char	*remake_var_line(char *line, int len)
{
	int		i;
	int		j;
	char	*tmp;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while (line[i] && i < len)
	{
		if (line[i] != '$' && i < len)
		{
			j = i;
			while (line[i] && line[i] != '$' && i < len)
				i++;
			tmp = ft_substr(line, j, i);
			str = ft_free_strjoin(str, tmp);
			free(tmp);
		}
		if (line[i] == '$' && (!line[i + 1] || line[i + 1] == ' '))
		{
			tmp = ft_substr(line, i, 2);
			str = ft_free_strjoin(str, tmp);
			free(tmp);
			if (!line[i + 1])
				i++;
			else
				i += 2;
		}
		else if (line[i] == '$' && i < len)
		{
			tmp = get_env_value(g_lobal->env, line, &i);
			str = ft_free_strjoin(str, tmp);
			free(tmp);
		}
	}
	return (str);
}
