/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:09:01 by ergrigor          #+#    #+#             */
/*   Updated: 2022/03/19 21:53:42 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	src1;
	size_t	x;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	src1 = dstlen;
	x = 0;
	if (dstsize == 0)
		return (srclen);
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	while (x < (dstsize - src1 - 1) && src[x])
	{
		dst[dstlen] = src[x];
		x++;
		dstlen++;
	}
	dst[dstlen] = '\0';
	return (src1 + srclen);
}
