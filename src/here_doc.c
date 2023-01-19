/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:55 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 22:46:12 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	hd_maker(t_token *token)
{
	t_token	*ptr;
	char	*doc;
	int		flag;

	g_lobal->hd_count++;
	flag = 0;
	ptr = NULL;
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

void	norm_make_doc(char *name, char *line, char *doc, int flag, int file)
{
	signal_call(2);
	name = get_doc_name();
	file = open(name, O_TRUNC | O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(set_status(1));
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
	g_lobal->all_fd[g_lobal->fd_index++] = open(name, O_RDONLY);
}

void	make_doc(char *doc, int flag)
{
	pid_t	pid;
	int		status;
	char	*line;
	char	*name;
	int		file;

	line = NULL;
	name = NULL;
	file = 0;
	pid = fork();
	signal (SIGQUIT, SIG_IGN);
	signal (SIGINT, SIG_IGN);
	if (pid == 0)
	{
		norm_make_doc(name, line, doc, flag, file);
		exit(0);
	}
	else
		hd_wait(&status, &pid);
}

char	*make_doc_name(t_token *token, int *flag)
{
	char	*res;
	t_token	*ptr;

	ptr = token;
	while (ptr && ptr->type != SPACE_TK && ptr->type != PIPE)
	{
		if (ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES)
		{
			*flag = 1;
			break ;
		}
		ptr = ptr->next;
	}
	res = concate_string(&token);
	return (res);
}
