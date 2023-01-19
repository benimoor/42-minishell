/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:51:37 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 20:08:35 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_token	*lexer(char *line)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		i;	

	i = 0;
	tokens = ft_calloc(sizeof(t_token), 1);
	while (line[i])
	{
		if (line[i] && is_word_tok(line[i]) == 0)
			make_word_tok(&tokens, line, &i);
		else if (line[i] && line[i] == '|')
			make_pipe_tok(&tokens, line, &i);
		else if (line[i] && line[i] == '<' && line[i + 1] != '<')
			make_redin_tok(&tokens, line, &i);
		else if (line[i] && line[i] == '<' && line[i + 1] == '<')
			make_here_tok(&tokens, line, &i);
		else if (line[i] && line[i] == '>' && line[i + 1] != '>')
			make_redout_tok(&tokens, line, &i);
		else if (line[i] && line[i] == '>' && line[i + 1] == '>')
			make_apply_tok(&tokens, line, &i);
		else if (line[i] && line[i] == ' ')
			make_space_tok(&tokens, line, &i);
		else if (line[i] && line[i] == '"')
			make_dbq_tok(&tokens, line, &i);
		else if (line[i] && line[i] == '\'')
			make_sqt_tok(&tokens, line, &i);
	}
	tmp_tok = tokens->next;
	free(tokens);
	return (tmp_tok);
}

t_token	*ft_toknew(char *line, int type, int len)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = line;
	new->type = type;
	new->len = len;
	new->next = NULL;
	return (new);
}

void	ft_tokadd_back(t_token **lst, t_token *new)
{
	t_token	*iter;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	iter = *lst;
	while (iter -> next != NULL)
		iter = iter -> next;
	iter -> next = new;
}
