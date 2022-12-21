/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:38:59 by ergrigor          #+#    #+#             */
/*   Updated: 2022/11/14 15:14:41 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	first_set_count(char const *str, char const *set)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (set[index])
	{
		if (set[index] == *str)
		{
			index = 0;
			count++;
			str++;
		}
		else
			index++;
	}
	return (count);
}

char	*ft_free_strjoin(char *s1, char *s2)
{
	char		*new_str;
	size_t		f_index;
	size_t		s_index;

	if (!s1)
		return(ft_strdup(s2));
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
	if(s1)
		free(s1);
	return (new_str);
}

char	*ft_str_start_trim(char const *s1, char const *set)
{
	size_t	lenght;
	size_t	start;
	size_t	str_len;
	char	*str;

	if (!*set || (first_set_count(s1, set) == 0))
	{
		str = ft_strdup(s1);
		return (str);
	}
	start = first_set_count(s1, set);
	lenght = ft_strlen(s1) - start;
	str = ft_substr(s1, start, lenght);
	str_len = ft_strlen(str);
	str[str_len] = '\0';
	return (str);
}

void	skip_spaces(int *i, int *arr)
{
	while (arr[*i] == SPACE_TK || arr[*i] == L_SCOPE || arr[*i] == R_SCOPE)
		(*i)++;
}

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
