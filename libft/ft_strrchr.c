/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:11:42 by ergrigor          #+#    #+#             */
/*   Updated: 2022/03/18 20:11:46 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*last;

	i = ft_strlen(s);
	last = (char *)s;
	while (i > 0)
	{
		if (last[i] == (char)c)
			return (last + i);
		i--;
	}
	if (last[i] == (char)c)
		return ((char *)last);
	return (NULL);
}
