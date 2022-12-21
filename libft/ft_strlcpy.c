/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:09:51 by ergrigor          #+#    #+#             */
/*   Updated: 2022/03/25 19:07:39 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	x;

	srclen = ft_strlen(src);
	x = 0;
	if (dstsize == 0)
		return (srclen);
	while (x < (dstsize - 1) && src[x])
	{
		dst[x] = src[x];
		x++;
	}
	dst[x] = '\0';
	return (srclen);
}
