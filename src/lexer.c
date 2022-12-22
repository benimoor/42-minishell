/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 05:07:46 by ergrigor          #+#    #+#             */
/*   Updated: 2022/12/22 15:40:20 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

int	is_word_tok(char c)
{
	if (c != '|' && c != '\'' && c != '"'
		&& c != '>'
		&& c != '<' && c != ' ' && c != '\0')
		return (0);
	return (1);
}

// void	lexer_norm1(char *line, t_token **token_ptr, int *i)
// {
// 	int		tmp;
// 	t_token	*tokens;

// 	tokens = *token_ptr;
// }

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

// void	make_or_tok(t_token **token_ptr, char *line, int *i)
// {
// 	t_token	*tokens;
// 	t_token	*tmp_tok;
// 	int		tmp;

// 	tokens = *token_ptr;
// 	tmp = *i;
// 	(*i) = (*i) + 2;
// 	if (tokens)
// 	{
// 		tmp_tok = ft_toknew(line + tmp, OR_IF, 2);
// 		ft_tokadd_back(token_ptr, tmp_tok);
// 	}
// 	else
// 		tokens = ft_toknew(line + tmp, OR_IF, 2);
// }

// void	make_and_tok(t_token **token_ptr, char *line, int *i)
// {
// 	t_token	*tokens;
// 	t_token	*tmp_tok;
// 	int		tmp;

// 	tokens = *token_ptr;
// 	tmp = *i;
// 	(*i) = (*i) + 2;
// 	if (tokens)
// 	{
// 		tmp_tok = ft_toknew(line + tmp, AND_OR, 2);
// 		ft_tokadd_back(token_ptr, tmp_tok);
// 	}
// 	else
// 		tokens = ft_toknew(line + tmp, AND_OR, 2);
// }

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

t_token	*lexer(char *line)
{
	t_token	*tokens;
	t_token	*tmp_tok;
	int		i;	
	int		tmp;

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
