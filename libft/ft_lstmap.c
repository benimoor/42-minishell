/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:44:09 by ergrigor          #+#    #+#             */
/*   Updated: 2022/03/20 17:36:22 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp;

	new_lst = ft_lstnew(f(lst -> content));
	if (!new_lst)
		return (NULL);
	lst = lst -> next;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
			ft_lstclear(&new_lst, del);
		ft_lstadd_back(&new_lst, tmp);
		lst = lst -> next;
	}
	return (new_lst);
}
