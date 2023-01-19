/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 19:28:02 by ergrigor          #+#    #+#             */
/*   Updated: 2022/10/11 17:08:33 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// 0 -> ""
// 1 -> ''
// 2 -> ()

int	fnorm_first_checker(int db_quot, int quot, int l_scope, int r_scope)
{
	if (l_scope != r_scope)
	{
		if (l_scope > r_scope)
			return (write(2, R_SCOPE_ERR, ft_strlen(R_SCOPE_ERR)), 1);
		else
			return (write(2, L_SCOPE_ERR, ft_strlen(R_SCOPE_ERR)), 1);
	}
	if ((quot % 2) != 0)
		return (write(2, QUOTE_ERR, ft_strlen(QUOTE_ERR)), 1);
	if ((db_quot % 2) != 0)
		return (write(2, DB_QUOTE_ERR, ft_strlen(DB_QUOTE_ERR)), 1);
	return (0);
}

void	skip_char(int *i, char *cmd_line, int *arr, char tok)
{
	(*arr)++;
	(*i)++;
	while (cmd_line[*i] && cmd_line[*i] != tok)
		(*i)++;
	if (cmd_line[*i] == tok)
		(*arr)++;
}

// 0	"db_quot";
// 1	'quot';
// 2	( l_scope;
// 3	) r_scope;
int	first_checker(char *cmd_line)
{
	int	i;
	int	arr[4];

	i = -1;
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = 0;
	while (cmd_line[++i])
	{
		if (cmd_line[i] == '"')
			skip_char(&i, cmd_line, &arr[0], '"');
		else if (cmd_line[i] == '\'')
			skip_char(&i, cmd_line, &arr[0], '\'');
		else if (cmd_line[i] == '(')
			arr[2] += 1;
		else if (cmd_line[i] == ')')
		{
			if (arr[2] > arr[3])
				arr[3] += 1;
			else
				return (write(2, L_SCOPE_ERR, ft_strlen(R_SCOPE_ERR)), 1);
		}
	}
	return (fnorm_first_checker(arr[0], arr[1], arr[2], arr[3]));
}
