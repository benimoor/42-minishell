/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:02:33 by ergrigor          #+#    #+#             */
/*   Updated: 2023/03/22 22:49:50 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_correct(t_token *ptr)
{
	int	flag;

	flag = 0;
	while (ptr && ptr->type != SPACE_TK && ptr->type != PIPE
		&& ptr->type != RED_INPUT && ptr->type != RED_OUTPUT
		&& ptr->type != RED_OUTPUT_APP && ptr->type != HERE_DOC)
	{
		if (ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES)
		{
			flag = ptr->type;
			if (!ptr->next)
				return (1);
			while (ptr->next && ptr->next->type != flag)
				ptr = ptr->next;
			if (!ptr->next || ptr->next->type != flag)
				return (1);
			flag = 1;
		}
		ptr = ptr->next;
	}
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
				ptr = ptr->next->next;
	else
		ptr = ptr->next;
	*tmp = ptr;
	if (is_correct(ptr) != 0)
		return (ft_putstr_fd("syntax error", 2), 2);
	file = concate_string(tmp);
	if (!file)
		return (1);
	if (open_file(file, flag) != 0)
		return (1);
	while (ptr && ptr->type != SPACE_TK && ptr->type != PIPE
		&& ptr->type != RED_INPUT && ptr->type != RED_OUTPUT
		&& ptr->type != RED_OUTPUT_APP && ptr->type != HERE_DOC)
		ptr = ptr->next;
	*tmp = ptr;
	return (free(file), 0);
}

int	open_file(char *file, int flag)
{
	if (flag == RED_INPUT)
		g_lobal->all_fd[g_lobal->fd_index] = open(file, O_RDONLY);
	else if (flag == RED_OUTPUT)
	{
		g_lobal->all_fd[g_lobal->fd_index]
			= open(file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	}
	else
		g_lobal->all_fd[g_lobal->fd_index]
			= open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	g_lobal->fd_index++;
	return (0);
}

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
