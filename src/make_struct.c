/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:58:08 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/05 23:50:47 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

void	skip_redir(t_token **tok)
{
	t_token	*ptr;
	int		flag;

	ptr = *tok;
	if (ptr->next->type == SPACE_TK)
		ptr = ptr->next->next;
	else
		ptr = ptr->next;
	if (ptr->type == WORD)
		ptr = ptr->next->next;
	else if (ptr->type == SINGLE_QUOTES || ptr->type == DOUBLE_QUOTES)
	{
		flag = ptr->type;
		while (ptr->next->type != flag)
			ptr = ptr->next;
		ptr = ptr->next->next;
	}	
	*tok = ptr;
}

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

t_command	*make_cmd(t_token **tok)
{
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	printf("%d\n", arg_count(*tok));
	while (1)
		;
	// while (*tok && (*tok)->type != PIPE)
	// {
	// 	cmd->args = ft
	// }
}

void	make_elem(t_token	**tok, t_element **elem)
{
	t_token		*ptr;
	t_command	*cmd;

	ptr = *tok;
	if (ptr->type == SPACE_TK)
		ptr = ptr->next;
	cmd = make_cmd(&ptr);
	(*elem)->command = cmd;
	(*elem)->next = ft_calloc(sizeof(t_element), 1);
	*elem = (*elem)->next;
}

void	make_struct(void)
{
	t_element	*ptr;
	t_token		*tok;

	ptr = ft_calloc(sizeof(t_element), 1);
	global->elem = ptr;
	tok = global->tokens;
	while (tok)
	{
		if (tok->type == PIPE)
		{
			ptr->delimiter = PIPE;
			ptr->type = 1;
		}
		else
			make_elem(&tok, &ptr);
		if (!tok || !tok->next)
			break ;
	}
}
