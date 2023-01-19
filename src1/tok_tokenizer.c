/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_tokenizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:35:44 by ergrigor          #+#    #+#             */
/*   Updated: 2022/10/22 17:05:41 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	tokenizer(char *cmd_line, int *arr, int len)
{
	int	i;

	i = 0;
	while (cmd_line[i] && i < len)
	{
		if (cmd_line[i] == ' ')
			arr[i] = SPACE_TK;
		else if (cmd_line [i] == '|' && cmd_line[i + 1] != '|')
			arr[i] = PIPE;
		else if (cmd_line [i] == '(')
			arr[i] = L_SCOPE;
		else if (cmd_line [i] == ')')
			arr[i] = R_SCOPE;
		else if (cmd_line [i] == '<' && cmd_line[i + 1] != '<')
			arr[i] = RED_INPUT;
		else if (cmd_line [i] == '>' && cmd_line[i + 1] != '>')
			arr[i] = RED_OUTPUT;
		else
			fnorm_tokenizer(cmd_line, arr, len, &i);
		i++;
	}
}

void	fnorm_tokenizer2(char *cmd_line, int *arr, int len, int *i)
{
	while (cmd_line[*i] && *i < len)
	{
		if (cmd_line[*i] == '"')
			arr[*i] = DOUBLE_QUOTES;
		else if (cmd_line[*i] == '\'')
			arr[*i] = SINGLE_QUOTES;
		else if (cmd_line[*i] == '*')
			arr[*i] = ASTERIX;
		else if (cmd_line[*i] == '$')
			arr[*i] = VARIABLE_TK;
		else if (cmd_line[*i] == '|' && cmd_line[(*i) + 1] == '|')
		{
			arr[(*i)++] = OR_IF;
			arr[(*i)] = OR_IF;
		}
		else
			arr[*i] = WORD;
		break ;
	}
}

void	fnorm_tokenizer(char *cmd_line, int *arr, int len, int *i)
{
	while (cmd_line[*i] && *i < len)
	{
		if (cmd_line[*i] == '>' && cmd_line[(*i) + 1] == '>')
		{
			arr[(*i)++] = RED_OUTPUT_APP;
			arr[(*i)] = RED_OUTPUT_APP;
		}
		else if (cmd_line[*i] == '<' && cmd_line[(*i) + 1] == '<')
		{
			arr[(*i)++] = HERE_DOC;
			arr[(*i)] = HERE_DOC;
		}
		else if (cmd_line[*i] == '&' && cmd_line[(*i) + 1] == '&')
		{
			arr[(*i)++] = AND_OR;
			arr[(*i)] = AND_OR;
		}
		else
			fnorm_tokenizer2(cmd_line, arr, len, i);
		break ;
	}
}

int	*tokenization(char *cmd_line)
{
	t_token	*tok_line;
	int		*arr;
	int		len;
	int		i;
	
	len = ft_strlen(cmd_line);
	arr = malloc ((len + 1) * sizeof(int));
	arr[len] = INT_MIN;
	i = 0;
	tokenizer(cmd_line, arr, len);
	quot_editor(arr, len);
	arg_counter(&i, arr);
	return (arr);
}
