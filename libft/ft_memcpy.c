/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:58:09 by ergrigor          #+#    #+#             */
/*   Updated: 2022/03/18 19:58:13 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void	*dst, const void *src, size_t n)
{
	unsigned char		*cpy;
	unsigned const char	*src_char;

	src_char = src;
	cpy = dst;
	while (n--)
	{
		*cpy = *src_char;
		src_char++;
		cpy++;
	}
	return (dst);
}
