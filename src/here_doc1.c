/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:37:57 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/08 10:08:42 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*mdn_norm(t_token *token, int flag1, int *flag, char **res)
{
	char	*tmp;

	*flag = 1;
	while (token->next && token->next->type != flag1)
	{
		token = token->next;
		tmp = ft_substr(token->str, 0, token->len);
		*res = ft_free_strjoin(*res, tmp);
		free(tmp);
	}
	if (token->next == NULL)
		return (free(*res), NULL);
	else
	{
		token = token->next->next;
		return (*res);
	}
}

char	*make_doc_name(t_token *token, int *flag)
{
	char	*res;
	int		flag1;

	res = ft_strdup("");
	while (token)
	{
		flag1 = token->type;
		if (flag1 == SINGLE_QUOTES || flag1 == DOUBLE_QUOTES)
			return (mdn_norm(token, flag1, flag, &res));
		else if (token->type == WORD)
		{
			res = ft_substr(token->str, 0, token->len);
			token = token->next;
			return (res);
		}
		else if (token->type == SPACE_TK)
		{
			if (token->next == NULL)
				return (free(res), NULL);
			token = token->next;
		}
		else
			return (free(res), NULL);
	}
	return (NULL);
}

char	*get_pid()
{
	char	*name;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		exit(0);
	else
	{
		wait(&status);
		name = ft_itoa((int)pid - 1);
	}
	return (name);
}

char	*get_dollar()
{
	t_env	*tmp;

	tmp = global->env;
	while (tmp)
	{
		if (ft_strlen(tmp->val_name) == 1
			&& ft_strncmp(tmp->val_name, "$", 1) == 0)
			return (ft_strdup(tmp->val_name));
		tmp = tmp->next;
	}
	return (NULL);
}
char	*get_doc_name()
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

int	no_var(char *line, size_t len)
{
	int	i;

	i = 0;
	while (line[i] && i < len)
	{
		if (line[i] == '$')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*remake_var_line(char *line, int len)
{
	int		i;
	int		j;
	char	*tmp;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while (line[i] && i < len)
	{
		j = i;
		while (line[i] && line[i] != '$' && i < len)
			i++;
		if (i != 0)
		{
			tmp = ft_substr(line, j, i);
			str = ft_free_strjoin(str, tmp);
			free(tmp);
		}
		if (line[i] == '$' && i < len)
		{
			tmp = get_env_value(global->env, line, &i);
			str = ft_free_strjoin(str, tmp);
			free(tmp);
		}
	}	
	return (str);
}

void put_in_file(char *line, int fd, int flag, size_t len)
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

void	make_doc(char *doc, int flag)
{
	pid_t	pid;
	int		status;
	char	*line;
	char	*name;
	int		file;

	pid = fork();
	if (pid == 0)
	{
		name = get_doc_name();
		file = open(name, O_TRUNC | O_WRONLY | O_APPEND | O_CREAT, 0644);
		while (1)
		{
			line = readline("> ");
			if (ft_strlen(line) != ft_strlen(doc)
				&& ft_strncmp(line, doc, ft_strlen(line)) != 0)
			{
				line = ft_free_strjoin(line, "\n");
				put_in_file(line, file, flag, ft_strlen(line));
				free(line);
			}
			else if (ft_strlen(line) == ft_strlen(doc)
				&& ft_strncmp(line, doc, ft_strlen(doc)) == 0)
			{
				free(line);
				break ;
			}
		}
		close(file);
		global->all_fd[global->fd_index++] = open(name, O_RDONLY);
		exit(0);
	}
	else
	{
		wait(&status);
	}
}

int	hd_maker(t_token *token)
{
	t_token	*ptr;
	char	*doc;
	int		flag;

	global->hd_count++;
	flag = 0;
	if (token->next && token->next->type == SPACE_TK)
		ptr = token->next->next;
	else if (token->next && token->next->type != SPACE_TK)
		ptr = token->next;
	else
	{
		token = ptr;
		return (ft_putstr_fd("Syntax Error\n", 2), -1);
	}
	doc = make_doc_name(ptr, &flag);
	token = ptr;
	if (doc != NULL)
		make_doc(doc, flag);
	else
		return (ft_putstr_fd("Syntax Error\n", 2), -1);
	free(doc);
	return (0);
}
