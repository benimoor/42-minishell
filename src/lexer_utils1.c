/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:53:02 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 17:55:52 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_word_tok(char c)
{
	if (c != '|' && c != '\'' && c != '"'
		&& c != '>'
		&& c != '<' && c != ' ' && c != '\0')
		return (0);
	return (1);
}

void	make_word_tok(t_token **token_ptr, char *line, int *i)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		tmp;
	int		tmp2;

	tokens = *token_ptr;
	tmp = *i;
	tmp2 = *i;
	while (is_word_tok(line[tmp2]) == 0)
			tmp2++;
	if (tokens)
	{
		tmp_tok = ft_toknew(line + tmp, WORD, (tmp2 - tmp));
		ft_tokadd_back(token_ptr, tmp_tok);
	}
	else
	{
		tokens = ft_toknew(line + tmp, WORD, (tmp2 - tmp));
	}
	*i = tmp2;
}

void	make_pipe_tok(t_token **token_ptr, char *line, int *i)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		tmp;

	tokens = *token_ptr;
	tmp = *i;
	(*i) = (*i) + 1;
	if (tokens)
	{
		tmp_tok = ft_toknew(line + tmp, PIPE, 1);
		ft_tokadd_back(token_ptr, tmp_tok);
	}
	else
		tokens = ft_toknew(line + tmp, PIPE, 1);
}

void	make_redin_tok(t_token **token_ptr, char *line, int *i)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		tmp;

	tokens = *token_ptr;
	tmp = *i;
	(*i) = (*i) + 1;
	if (tokens)
	{
		tmp_tok = ft_toknew(line + tmp, RED_INPUT, 1);
		ft_tokadd_back(token_ptr, tmp_tok);
	}
	else
		tokens = ft_toknew(line + tmp, RED_INPUT, 1);
}

void	make_here_tok(t_token **token_ptr, char *line, int *i)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		tmp;

	tokens = *token_ptr;
	tmp = *i;
	(*i) = (*i) + 2;
	if (tokens)
	{
		tmp_tok = ft_toknew(line + tmp, HERE_DOC, 2);
		ft_tokadd_back(token_ptr, tmp_tok);
	}
	else
		tokens = ft_toknew(line + tmp, HERE_DOC, 2);
}
