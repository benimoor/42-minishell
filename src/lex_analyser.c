/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_analyser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:00:05 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/27 00:12:57 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	qt_analyser(t_token **token)
{
	t_token	*ptr;

	ptr = *token;
	if (ptr->type == DOUBLE_QUOTES)
	{
		ptr = ptr->next;
		while (ptr && ptr->type != DOUBLE_QUOTES)
			ptr = ptr->next;
		if (ptr && ptr->type == DOUBLE_QUOTES)
			ptr = ptr->next;
		else
			return (ft_putstr_fd("Error DBQT\n", 2), set_status(258));
	}
	else if (ptr->type == SINGLE_QUOTES)
	{
		while (ptr->next && ptr->next->type != SINGLE_QUOTES)
			ptr = ptr->next;
		if (ptr->next && ptr->next->type == SINGLE_QUOTES)
			ptr = ptr->next->next;
		else
			return (ft_putstr_fd("Error SQT\n", 2), set_status(258));
	}
	*token = ptr;
	return (0);
}

int	analyser_part1(t_token **token)
{
	t_token	*ptr;

	ptr = *token;
	
	if (ptr && ptr->type == HERE_DOC && hd_maker(&ptr) == -1)
	{
		return (set_status(1));
	}
	else if (ptr && (ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES))
	{
		if (qt_analyser(&ptr) != 0)
			return (get_status());
	}
	else if (ptr && (ptr->type == RED_INPUT || ptr->type == RED_OUTPUT
			|| ptr->type == RED_OUTPUT_APP))
	{
		if (make_open(&ptr) != 0)
			return (ft_putstr_fd("\n", 2), set_status(1));
	}
	else if (ptr && ptr->type == WORD)
	{
		ptr = ptr->next;
	}
	*token = ptr;
	return (0);
}

int	analyse_part2(t_token **token)
{
	t_token	*ptr;

	ptr = *token;
	if (!ptr || (ptr && ptr->type != PIPE && ptr->type != SPACE_TK))
		return (0);
	if (ptr && ptr->type == PIPE)
	{
		ptr = ptr->next;
		if (ptr && ptr->type == SPACE_TK)
			ptr = ptr->next;
		if (!ptr || ptr->type == PIPE)
			return (set_status(258), ft_putstr_fd("PIPE Error\n", 2), 1);
	}
	else if (ptr && ptr->type == SPACE_TK)
	{
		ptr = ptr->next;
	}
	// else
	// {
	// 	if (ptr)
	// 		ptr = ptr->next;
	// 	return (0);
	// }
	*token = ptr;
	return (0);
}

int	lex_analyser(t_token *token)
{
	t_token	*ptr;

	ptr = token;
	g_lobal->fd_index = 3;
	g_lobal->hd_count = 0;
	if (ptr->type == PIPE || (ptr->type == SPACE_TK
			&& ptr->next && ptr->next->type == PIPE))
		return (set_status(258), ft_putstr_fd("PIPE Error\n", 2), 1);
	if (hd_count_check(ptr) > 16)
		return (ft_putstr_fd("maximum here-document count exceeded\n", 2), 1);
	while (ptr)
	{
		if (ptr && analyser_part1(&ptr) != 0)
		{
			return (get_status());
		}
		else if (ptr && analyse_part2(&ptr) != 0)
		{
			return (get_status());
		}
	}
	set_status(0);
	return (0);
}
