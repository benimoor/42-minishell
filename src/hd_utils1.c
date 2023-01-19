/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:08:06 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 18:10:34 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*concate_string(t_token **token)
{
	t_token	*ptr;
	char	*res;
	char	*tmp;
	char	*tmp2;
	int		flag;

	ptr = *token;
	res = ft_strdup("");
	while (ptr && ptr->type != SPACE_TK && ptr->type != PIPE && !(ptr->type == HERE_DOC || ptr->type == RED_OUTPUT_APP
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

char	*get_dollar(void)
{
	t_env	*tmp;

	tmp = global->env;
	while (tmp)
	{
		if (ft_strlen(tmp->val_name) == 1
			&& ft_strncmp(tmp->val_name, "$", 1) == 0)
			return (ft_strdup(tmp->val_value));
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_doc_name(void)
{
	char	*index;
	char	*tmp;
	char	*name;

	tmp = get_dollar();
	index = ft_itoa(global->hd_count);
	name = ft_strdup("/tmp/.mini_hd_");
	name = ft_free_strjoin(name, tmp);
	name = ft_free_strjoin(name, "_");
	name = ft_free_strjoin(name, index);
	free(index);
	free(tmp);
	return (name);
}

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