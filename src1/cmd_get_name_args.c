/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_name_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:38:51 by ergrigor          #+#    #+#             */
/*   Updated: 2022/10/30 04:30:41 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	arg_counter(int *i, int *arr)
{
	int	count;
	int	x;

	count = 0;
	x = *i;
	skip_spaces(&x, arr);
	if (arr[x] == PIPE || arr[x] == AND_OR || arr[x] == OR_IF
		|| arr[x] == R_SCOPE || arr[x] == L_SCOPE)
		return (0);
	while (arr[x] != PIPE && arr[x] != AND_OR && arr[x] != OR_IF
		&& arr[x] != INT_MIN && arr[x] != R_SCOPE && arr[x] != L_SCOPE)
	{
		while (arr[x] != PIPE && arr[x] != AND_OR && arr[x] != OR_IF
			&& arr[x] != INT_MIN && arr[x] != SPACE_TK && arr[x] != R_SCOPE
			&& arr[x] != L_SCOPE)
			x++;
		if (arr[x] == SPACE_TK || arr[x] == L_SCOPE || arr[x] == R_SCOPE)
			skip_spaces(&x, arr);
		count++;
	}
	return (count);
}

char	*get_arg(int *i, int *arr, char *line)
{
	char	*str;
	int		x;

	skip_spaces(i, arr);
	x = *i;
	if (arr[x] == PIPE || arr[x] == AND_OR || arr[x] == OR_IF
		|| arr[x] == R_SCOPE)
		return (0);
	while (arr[x] != PIPE && arr[x] != AND_OR && arr[x] != OR_IF
		&& arr[x] != INT_MIN && arr[x] != SPACE_TK && arr[x] != R_SCOPE)
	{
		while (arr[x] != PIPE && arr[x] != AND_OR && arr[x] != OR_IF
			&& arr[x] != INT_MIN && arr[x] != SPACE_TK && arr[x] != R_SCOPE)
			x++;
		str = ft_substr(line, *i, (x - (*i)));
		*i = x;
	}
	return (str);
}

void	get_cmd_name(int *i, int *arr, t_element *elem, char *line)
{
	int	x;

	x = *i;
	while (arr[x] != SPACE_TK && arr[x] != R_SCOPE && arr[x] != INT_MIN)
		x++;
	elem->command->cmd = ft_substr(line, *i, (x - (*i)));
}

void	get_cmd_args(int *i, int *arr, t_element *elem, char *line)
{
	int	size;
	int	x;

	x = 0;
	skip_spaces(i, arr);
	if (arr[*i] == PIPE || arr[*i] == AND_OR
		|| arr[*i] == OR_IF || arr[*i] == R_SCOPE)
		return ;
	size = arg_counter(i, arr);
	elem->command->args = ft_calloc(size + 1, sizeof(char *));
	while (x < size)
	{
		elem->command->args[x] = get_arg(i, arr, line);
		x++;
	}
	return ;
}
