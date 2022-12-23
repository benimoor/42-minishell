/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 16:37:57 by ergrigor          #+#    #+#             */
/*   Updated: 2022/12/23 18:10:01 by ergrigor         ###   ########.fr       */
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

char	*get_doc_name()
{
	char	*index;
	char	*name;

	index = ft_itoa(hd_count);
	name = ft_strdup("/tmp/mini_hd");
	name = ft_free_strjoin(name, index);
	free(index);
	return (name);
}

void put_in_file(char *line, int fd, int flag, size_t len)
{
	
	if (flag == 0)
		write(fd, line, len);
	else
	{
		
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

	hd_count++;
	flag = 0;
	if (token->next && token->next->type == SPACE_TK)
		ptr = token->next->next;
	else if (token->next && token->next->type != SPACE_TK)
		ptr = token->next;
	else
	{
		token = ptr;
		printf("Syntax Error\n");
		return -1;
	}
	doc = make_doc_name(ptr, &flag);
	token = ptr;
	if (doc != NULL)
		make_doc(doc, flag);
		// printf("%s\n", doc);÷
	else
	{
		printf("Syntax Error\n");
		return -1;
	}
	free(doc);
	return (0);
}
