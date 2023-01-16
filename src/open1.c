/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 19:49:39 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/16 23:55:37 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// void	makefd(void)
// {
// 	global->fd_index = 3;
// 	global->all_fd[0] = dup(0);
// 	global->all_fd[1] = dup(1);
// 	global->all_fd[2] = dup(2);
// }

char	*get_file_name(t_token *ptr)
{
	char	*res;

	res = remake_var_line(ptr->str, ptr->len);
	return (res);
}

char	*get_qtfile_name(t_token *ptr)
{
	char	*res;
	char	*tmp;
	int		flag;

	flag = ptr->type;
	res = ft_strdup("");
	ptr = ptr->next;
	if (ptr->type == flag)
		return (ft_putstr_fd("No such file or directory\n", 2), NULL);
	while (ptr && ptr->type != flag)
	{
		tmp = remake_var_line(ptr->str, ptr->len);
		res = ft_free_strjoin(res, tmp);
		free(tmp);
		ptr = ptr->next;
		if (!ptr)
			return (ft_putstr_fd("syntax error\n", 2), free(res), NULL);
	}
	ptr = ptr->next;
	return (res);
}

int	open_file(char *file, int flag)
{
	if (flag == RED_INPUT)
		global->all_fd[global->fd_index] = open(file, O_RDONLY);
	else if (flag == RED_OUTPUT)
		global->all_fd[global->fd_index]
			= open(file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	else
		global->all_fd[global->fd_index]
			= open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (global->all_fd[global->fd_index] < 0)
		return (ft_putstr_fd("minishell : file opening error\n", 2), 1);
	global->fd_index++;
	return (0);
}

int	make_open(t_token **tmp)
{
	char	*file;
	t_token	*ptr;
	int		flag;

	ptr = *tmp;
	flag = ptr->type;
	if (ptr->next && ptr->next->type == SPACE_TK)
				ptr = ptr->next;
	if (ptr->next && (ptr->next->type == DOUBLE_QUOTES
			|| ptr->next->type == SINGLE_QUOTES))
	{
		ptr = ptr->next;
		file = get_qtfile_name(ptr);
		if (file == NULL)
			return (1);
	}
	else if (ptr->next && ptr->next->type == WORD)
	{
		ptr = ptr->next;
		file = get_file_name(ptr);
		ptr = ptr->next;
	}
	else
		return (ft_putstr_fd("syntax error\n", 2), 1);
	if (open_file(file, flag) != 0)
		return (1);
	*tmp = ptr;
	return (free(file), 0);
}
