/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:09:35 by ergrigor          #+#    #+#             */
/*   Updated: 2022/03/18 20:09:35 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	joined_str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!joined_str)
		return (NULL);
	while (s1[i] != '\0')
	{
		joined_str[j] = s1[i];
		j++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		joined_str[j] = s2[i];
		j++;
		i++;
	}
	joined_str[j] = '\0';
	return (joined_str);
}
