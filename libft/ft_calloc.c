/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:30:33 by ergrigor          #+#    #+#             */
/*   Updated: 2022/03/18 19:53:48 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	char	*mem;

	total = count * size;
	mem = malloc(total);
	if (mem == NULL)
		return (NULL);
	ft_bzero(mem, total);
	return (mem);
}
