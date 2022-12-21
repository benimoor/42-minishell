/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_command_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:21:00 by ergrigor          #+#    #+#             */
/*   Updated: 2022/11/04 16:49:21 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	get_cmd_count(int *arr)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arr[i] != INT_MIN)
	{
		while (arr[i] == SPACE_TK && arr[i] != INT_MIN)
			i++;
		while (arr[i] != PIPE && arr[i] != AND_OR
			&& arr[i] != OR_IF && arr[i] != INT_MIN)
			i++;
		count++;
		if (arr[i] == INT_MIN)
			break ;
		if ((arr[i] == AND_OR || arr[i] == OR_IF) && arr[i] != INT_MIN)
			i += 2;
		if ((arr[i - 2] == AND_OR || arr[i - 2] == OR_IF))
			count++;
		if (arr[i] == PIPE && arr[i] != INT_MIN)
			i++;
		if (arr[i - 1] == PIPE)
			count++;
	}
	return (count);
}

void	fnorm_get_cmd(int *i, int *arr, t_element *elem, char *line)
{
	int			x;
	int			y;

	x = 0;
	elem->command = malloc(sizeof(t_command));
	get_cmd_name(i, arr, elem, line);
	get_cmd_args(i, arr, elem, line);
}

char	*and_or_doc(int *i, int *arr)
{
	if (arr[*i] == OR_IF)
		return (ft_strdup("||"));
	else if (arr[*i] == AND_OR)
		return (ft_strdup("&&"));
	else if (arr[*i] == HERE_DOC)
		return (ft_strdup(">>"));
	return (NULL);
}

void print_elem(t_element *elem)
{
	if (elem->command && elem->command->cmd)
		printf("command : %s\n", elem->command->cmd);
	if (elem->command->args)
	{
		printf("args :");
		for (int u = 0; elem->command->args[u] != NULL; u++)
			printf("%s, ", elem->command->args[u]);
		printf("\n");
	}
}

void	get_cmd(int *i, int *arr, t_element *elem, char *line)
{
	while (arr[*i] != INT_MIN)
	{
		if (arr[*i] == PIPE)
		{
			elem->command = malloc(sizeof(t_command));
			elem->command->cmd = ft_strdup("|");
			elem->delimiter = PIPE;
			elem->type = 2;
			(*i)++;
			break ;
		}
		else if (arr[*i] == AND_OR || arr[*i] == OR_IF || arr[*i] == HERE_DOC)
		{
			elem->command = malloc(sizeof(t_command));
			elem->command->cmd = and_or_doc(i, arr);
			elem->delimiter = arr[*i];
			elem->type = 2;
			(*i) += 2;
			break ;
		}
		else
			fnorm_get_cmd(i, arr, elem, line);
		break ;
	}
}

t_element	**cmd_init(char *line, int *arr)
{
	t_element	**elem;
	int			size;
	int			i;
	int			x;

	x = 0;
	i = 0;
	size = get_cmd_count(arr);
	elem = malloc((size + 1) * sizeof(t_element *));
	elem[size] = 0;
	while (x < size && arr[i] != INT_MIN)
	{
		skip_spaces(&i, arr);
		elem[x] = malloc(sizeof(t_element));
		get_cmd(&i, arr, elem[x], line);
		x++;
	}
	return (elem);
}
