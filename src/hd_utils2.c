/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor <ergrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 20:51:09 by ergrigor          #+#    #+#             */
/*   Updated: 2023/03/22 20:55:38 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	put_in_file(char *line, int fd, int flag, size_t len)
{
	char	*new_line;

	if (flag == 1 || (flag == 0 && no_var(line, ft_strlen(line)) == 0))
		write(fd, line, len);
	else
	{
		new_line = remake_var_line(line, ft_strlen(line));
		write(fd, new_line, ft_strlen(new_line));
		free(new_line);
	}
}

void	hd_wait(int *status, pid_t *pid)
{
	waitpid(*pid, status, 0);
	if (WIFEXITED(*status))
		set_status(WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
	{
		write(1, "\n", 1);
		set_status(WTERMSIG(*status) + 128);
	}
}

int	get_status(void)
{
	t_env	*ptr;

	ptr = g_lobal->env;
	while (ptr)
	{
		if (ft_strcmp(ptr->val_name, "?") == 0)
			return (ft_atoi(ptr->val_value));
		ptr = ptr->next;
	}
	return (-1);
}

char	*make_res(t_token **token, t_token *ptr)
{
	int		f;
	char	*res;

	if (ptr && (ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES))
	{
		f = ptr->type;
		if (ptr->next && ptr->next->type == f)
		{
			ptr = ptr->next;
			if (!ptr->next || (ptr->next && (ptr->next->type == SPACE_TK
						|| ptr->next->type == PIPE)))
				return (ft_strdup(""));
		}
	}
	res = concate_string(token);
	if (!*res)
	{
		if (*token && ((*token)->type == RED_INPUT
				|| (*token)->type == RED_OUTPUT
				|| (*token)->type == RED_OUTPUT_APP))
				(*token) = (*token)->next;
		return (NULL);
	}
	return (res);
}

char	*make_doc_name(t_token **token, int *flag)
{
	char	*res;
	t_token	*ptr;

	ptr = *token;
	while (ptr && ptr->type != SPACE_TK && ptr->type != PIPE
		&& ptr->type != RED_INPUT && ptr->type != RED_OUTPUT
		&& ptr->type != RED_OUTPUT_APP && ptr->type != HERE_DOC)
	{
		if (ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES)
		{
			*flag = ptr->type;
			if (!ptr->next)
				return (NULL);
			while (ptr->next && ptr->next->type != *flag)
				ptr = ptr->next;
			if (!ptr->next || ptr->next->type != *flag)
				return (NULL);
			*flag = 1;
		}
		ptr = ptr->next;
	}
	res = make_res(token, ptr);
	*token = ptr;
	return (res);
}
