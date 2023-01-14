/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 22:58:08 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/14 16:48:57 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/main.h"

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

char	*concate_word(t_token **tok)
{
	char	*res;
	int		flag;
	char	*tmp;
	char	*tmp2;
	t_token	*ptr;

	res = remake_var_line((*tok)->str, (*tok)->len);
	ptr = (*tok)->next;
	flag = ptr->type;
	tmp = ft_strdup("");
	while (ptr->next && ptr->next->type != flag)
	{
		if (flag == DOUBLE_QUOTES)
			tmp2 = remake_var_line(ptr->next->str, ptr->next->len);
		else
			tmp2 = ft_substr(ptr->next->str, 0, ptr->next->len);
		tmp = ft_free_strjoin(tmp, tmp2);
		free(tmp2);
		ptr = ptr->next;
	}
	*tok = ptr->next->next;
	res = ft_free_strjoin(res, tmp);
	return (free(tmp), res);
}

char	*concate_quotes(t_token **tok)
{
	int		flag;
	char	*tmp;
	char	*tmp2;
	t_token	*ptr;

	ptr = (*tok);
	flag = (*tok)->type;
	tmp = ft_strdup("");
	while (ptr->next && ptr->next->type != flag)
	{
		if (flag == DOUBLE_QUOTES)
			tmp2 = remake_var_line(ptr->next->str, ptr->next->len);
		else
			tmp2 = ft_substr(ptr->next->str, 0, ptr->next->len);
		tmp = ft_free_strjoin(tmp, tmp2);
		//printf("res is [%s]\n", tmp);
		free(tmp2);
		ptr = ptr->next;
	}
	*tok = ptr->next->next;
	return (tmp);
}

char	*concate_string(t_token **token)
{
	t_token	*ptr;
	char	*res;
	char	*tmp;
	char	*tmp2;
	int		flag;

	ptr = *token;
	res = ft_strdup("");
	while (ptr && ptr->type != SPACE_TK && ptr->type != PIPE  && !(ptr->type == HERE_DOC || ptr->type == RED_OUTPUT_APP
			|| ptr->type == RED_OUTPUT || ptr->type == RED_INPUT))
	{
		if (ptr->type == WORD)
		{
			tmp = remake_var_line(ptr->str, ptr->len);
			res = ft_free_strjoin(res, tmp);
			free(tmp);
			ptr = ptr->next;
		}
		else if (ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES)
		{
			flag = ptr->type;
			tmp2 = ft_strdup("");
			while (ptr->next->type != flag)
			{
				tmp = ft_substr(ptr->next->str, 0, ptr->next->len);
				tmp2 = ft_free_strjoin(tmp2, tmp);
				free(tmp);
				ptr = ptr->next;
			}
			ptr = ptr->next->next;
			if (flag == DOUBLE_QUOTES)
			{
				tmp = remake_var_line(tmp2, ft_strlen(tmp2));
				free(tmp2);
			}
			else
				tmp = tmp2;
			res = ft_free_strjoin(res, tmp);
			free(tmp);
		}
	}
	*token = ptr;
	return (res);
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
		else //if (ptr->type == WORD || ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES)
		{
			cmd->args[i++] = concate_string(&ptr);
		}
	}
	*tok = ptr;
}

t_command	*make_cmd(t_token **tok)
{
	t_command	*cmd;
	int			i;

	i = 0;
	cmd = ft_calloc(sizeof(t_command), 1);
	cmd->in = 0;
	cmd->out = 1;
	cmd->err = 2;
	fill_cmd(cmd, arg_count(*tok), tok);
	if (cmd && cmd->args)
		cmd->cmd = cmd->args[0];
	if (cmd && cmd->args)
	{
		printf("cmd is [%s]\n", cmd->cmd);
		while (cmd->args[i])
			printf("[%s] ", cmd->args[i++]);
		printf("\n");
	}
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
	(*elem)->next = ft_calloc(sizeof(t_element), 1);
	*elem = (*elem)->next;
	*tok = ptr;
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
			ptr->next = ft_calloc(sizeof(t_element), 1);
			ptr = ptr->next;
			tok = tok->next;
		}
		else
			make_elem(&tok, &ptr);
		if (!tok || !tok->next)
			break ;
	}
	ptr = global->elem;
	while (ptr->next)
		ptr = ptr->next;
	free(ptr->next);
	ptr->next = 0x0;
}
