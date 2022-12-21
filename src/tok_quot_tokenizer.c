/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_quot_tokenizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:08:59 by ergrigor          #+#    #+#             */
/*   Updated: 2022/10/22 16:35:13 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	make_single_quote(int *arr, int len, int *i)
{
	(*i)++;
	while (arr[*i] != SINGLE_QUOTES)
	{
		arr[*i] = WORD;
		(*i)++;
	}
}

void	make_double_quote(int *arr, int len, int *i)
{
	(*i)++;
	while (arr[*i] != DOUBLE_QUOTES && *i < len)
	{
		if (arr[*i] == VARIABLE_TK)
		{
			while (arr[*i] != SPACE_TK && arr[*i] != DOUBLE_QUOTES
				&& arr[*i] != SINGLE_QUOTES)
			{
				arr[*i] = VARIABLE_TK;
				(*i)++;
			}
		}
		if (arr[*i] == DOUBLE_QUOTES)
			break ;
		arr[*i] = WORD;
		(*i)++;
	}
	(*i)++;
}

void	quot_editor(int *arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (i == len)
			return ;
		if (arr[i] == SINGLE_QUOTES)
			make_single_quote(arr, len, &i);
		if (arr[i] == DOUBLE_QUOTES)
			make_double_quote(arr, len, &i);
		else
			i++;
	}
}
