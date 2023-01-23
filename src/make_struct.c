/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:11:25 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/24 00:24:55 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	make_struct(void)
{
	t_element	*ptr;
	t_token		*tok;

	ptr = ft_calloc(sizeof(t_element), 1);
	g_lobal->elem = ptr;
	tok = g_lobal->tokens;
	while (tok)
	{
		if (tok->type == PIPE)
			tok = tok->next;
		else
			make_elem(&tok, &ptr);
		if (!tok)
			break ;
	}
	ptr = g_lobal->elem;
	while (ptr->next && ptr->next->next)
		ptr = ptr->next;
	if (ptr->next->next)
		free(ptr->next->next);
	free(ptr->next);
	ptr->next = 0x0;
}

t_command	*make_cmd(t_token **tok)
{
	t_command	*cmd;
	int			i;

	i = 0;
	cmd = ft_calloc(sizeof(t_command), 1);
	cmd->in = g_lobal->all_fd[0];
	cmd->out = g_lobal->all_fd[1];
	cmd->err = g_lobal->all_fd[2];
	fill_cmd(cmd, arg_count(*tok), tok);
	if (cmd && cmd->args)
		cmd->cmd = cmd->args[0];
	return (cmd);
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
	//printf("[%d]\n", ptr->type);
	(*elem)->next = ft_calloc(sizeof(t_element), 1);
	*elem = (*elem)->next;
	*tok = ptr;
}
