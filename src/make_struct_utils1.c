/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:13:23 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 18:15:17 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	arg_count(t_token *tok)
{
	t_token	*ptr;
	int		res;
	int		flag;

	res = 0;
	ptr = tok;
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == SPACE_TK)
			ptr = ptr->next;
		else if (ptr->type == WORD)
		{
			res++;
			ptr = ptr->next;
		}
		else if (ptr->type == SINGLE_QUOTES || ptr->type == DOUBLE_QUOTES)
		{
			flag = ptr->type;
			while (ptr->next->type != flag)
				ptr = ptr->next;
			ptr = ptr->next->next;
			res++;
		}
		else if (ptr->type == HERE_DOC || ptr->type == RED_OUTPUT_APP
			|| ptr->type == RED_OUTPUT || ptr->type == RED_INPUT)
		{
			skip_redir(&ptr);
		}
	}
	return (res);
}

void	skip_redir(t_token **tok)
{
	t_token	*ptr;
	int		flag;

	ptr = *tok;
	if (ptr->next && ptr->next->type == SPACE_TK)
		ptr = ptr->next->next;
	else
		ptr = ptr->next;
	if (ptr && ptr->type == WORD)
	{
		ptr = ptr->next;
	}
	if (ptr && (ptr->type == SINGLE_QUOTES || ptr->type == DOUBLE_QUOTES))
	{
		flag = ptr->type;
		while (ptr->next && ptr->next->type != flag)
			ptr = ptr->next;
		if (ptr->next->next)
			ptr = ptr->next->next;
		else
			ptr = NULL;
	}	
	*tok = ptr;
}

void	fill_cmd(t_command *cmd, int arg_count, t_token	**tok)
{
	t_token	*ptr;
	int		hd;
	int		i;

	i = 0;
	hd = 3;
	ptr = *tok;
	cmd->args = ft_calloc(sizeof(char *), arg_count + 1);
	while (ptr && ptr->type != PIPE)
	{
		if (ptr->type == HERE_DOC || ptr->type == RED_INPUT || ptr->type == RED_OUTPUT || ptr->type == RED_OUTPUT_APP)
		{
			skip_redir(&ptr);
		}
		else if (ptr->type == SPACE_TK)
		{
			ptr = ptr->next;
		}
		else if (ptr->type == WORD || ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES)
		{
			cmd->args[i++] = concate_string(&ptr);
		}
	}
	*tok = ptr;
}