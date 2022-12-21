/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:04:43 by ergrigor          #+#    #+#             */
/*   Updated: 2022/03/24 23:42:42 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	tar;

	if (!c)
		return ((char *)str + ft_strlen(str));
	tar = c;
	while (*str)
	{
		if (*str == tar)
			return ((char *)str);
		else if (!*str++)
			return (0);
	}
	return (0);
}
