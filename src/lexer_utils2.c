/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:56:06 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 17:58:58 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	make_redout_tok(t_token **token_ptr, char *line, int *i)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		tmp;

	tokens = *token_ptr;
	tmp = *i;
	(*i) = (*i) + 1;
	if (tokens)
	{
		tmp_tok = ft_toknew(line + tmp, RED_OUTPUT, 1);
		ft_tokadd_back(token_ptr, tmp_tok);
	}
	else
		tokens = ft_toknew(line + tmp, RED_OUTPUT, 1);
}

void	make_apply_tok(t_token **token_ptr, char *line, int *i)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		tmp;

	tokens = *token_ptr;
	tmp = *i;
	(*i) = (*i) + 2;
	if (tokens)
	{
		tmp_tok = ft_toknew(line + tmp, RED_OUTPUT_APP, 2);
		ft_tokadd_back(token_ptr, tmp_tok);
	}
	else
		tokens = ft_toknew(line + tmp, RED_OUTPUT_APP, 2);
}

void	make_space_tok(t_token **token_ptr, char *line, int *i)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		tmp;
	int		tmp2;

	tokens = *token_ptr;
	tmp = *i;
	tmp2 = *i;
	while (line[tmp2] == ' ')
			tmp2++;
	if (tokens)
	{
		tmp_tok = ft_toknew(line + tmp, SPACE_TK, (tmp2 - tmp));
		ft_tokadd_back(token_ptr, tmp_tok);
	}
	else
		tokens = ft_toknew(line + tmp, SPACE_TK, (tmp2 - tmp));
	*i = tmp2;
}

void	make_dbq_tok(t_token **token_ptr, char *line, int *i)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		tmp;

	tokens = *token_ptr;
	tmp = *i;
	(*i) = (*i) + 1;
	if (tokens)
	{
		tmp_tok = ft_toknew(line + tmp, DOUBLE_QUOTES, 1);
		ft_tokadd_back(token_ptr, tmp_tok);
	}
	else
		tokens = ft_toknew(line + tmp, DOUBLE_QUOTES, 1);
}

void	make_sqt_tok(t_token **token_ptr, char *line, int *i)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		tmp;

	tokens = *token_ptr;
	tmp = *i;
	(*i) = (*i) + 1;
	if (tokens)
	{
		tmp_tok = ft_toknew(line + tmp, SINGLE_QUOTES, 1);
		ft_tokadd_back(token_ptr, tmp_tok);
	}
	else
		tokens = ft_toknew(line + tmp, SINGLE_QUOTES, 1);
}
