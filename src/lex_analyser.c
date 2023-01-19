/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analyser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:00:05 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 19:41:05 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	lex_analyser(t_token *token)
{
	t_token	*ptr;
	int		res;

	ptr = token;
	global->fd_index = 3;
	global->hd_count = 0;
	if (ptr->type == PIPE || (ptr->type == SPACE_TK
			&& ptr->next && ptr->next->type == PIPE))
		return (set_status(258), ft_putstr_fd("PIPE Error\n", 2), 1);
	if (hd_count_check(ptr) > 16)
		return (ft_putstr_fd("maximum here-document count exceeded\n", 2), 1);
	while (ptr)
	{
		if (ptr->type == DOUBLE_QUOTES)
		{
			ptr = ptr->next;
			while (ptr && ptr->type != DOUBLE_QUOTES)
				ptr = ptr->next;
			if (ptr && ptr->type == DOUBLE_QUOTES)
				ptr = ptr->next;
			else
				return (set_status(258), ft_putstr_fd("Error DBQT\n", 2), 1);
		}
		else if (ptr->type == SINGLE_QUOTES)
		{
			while (ptr->next && ptr->next->type != SINGLE_QUOTES)
				ptr = ptr->next;
			if (ptr->next && ptr->next->type == SINGLE_QUOTES)
				ptr = ptr->next->next;
			else
				return (set_status(258), ft_putstr_fd("Error SQT\n", 2), 1);
		}
		else if (ptr->type == RED_INPUT || ptr->type == RED_OUTPUT
			|| ptr->type == RED_OUTPUT_APP)
		{
			if (make_open(&ptr) != 0)
				return (set_status(1), ft_putstr_fd("Can not open file\n", 2), 1);
		}
		else if (ptr->type == WORD)
		{
			ptr = ptr->next;
		}
		else if (ptr->type == HERE_DOC && hd_maker(ptr) == -1)
			return (set_status(1), 1);
		else if (ptr->type == PIPE)
		{
			ptr = ptr->next;
			if (ptr && ptr->type == SPACE_TK)
				ptr = ptr->next;
			if (!ptr || ptr->type == PIPE)
				return (set_status(258), ft_putstr_fd("PIPE Error\n", 2), 1);
		}
		else if (ptr->type == SPACE_TK)
		{
			ptr = ptr->next;
		}
		else
		{
			//printf("stuc?\n");
			//printf("ptr->type? %d\n", ptr->type);
			ptr = ptr->next;
		}	
	}
	set_status(0);
	return (0);
}
