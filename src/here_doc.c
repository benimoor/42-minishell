/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:55 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/29 17:02:12 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	hd_maker(t_token **token)
{
	t_token	*ptr;
	char	*doc;
	int		flag;

	g_lobal->hd_count++;
	flag = 0;
	ptr = NULL;
	if ((*token)->next && (*token)->next->type == SPACE_TK)
		ptr = (*token)->next->next;
	else if ((*token)->next && (*token)->next->type != SPACE_TK)
		ptr = (*token)->next;
	else
	{
		*token = ptr;
		return (ft_putstr_fd("Syntax Error\n", 2), -1);
	}
	doc = make_doc_name(&ptr, &flag);
	*token = ptr;
	if (doc != NULL)
		make_doc(doc, flag);
	else
		return (ft_putstr_fd("Syntax Error\n", 2), -1);
	free(doc);
	return (0);
}

char	*handle_line(char *fl, char *line)
{
	line = ft_free_strjoin(line, "\n");
	fl = ft_free_strjoin(fl, line);
	free(line);
	return (fl);
}

void	put_in_file_and_close(char *fl, int file, int flag, int len)
{
	put_in_file(fl, file, flag, len);
	free(fl);
	close(file);
	exit(0);
}

void	norm_make_doc(char *name, char *doc, int flag, int file)
{
	char	*line;
	char	*fl;

	(void)name;
	fl = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			put_in_file(fl, file, flag, ft_strlen(fl));
			exit(set_status(1));
		}
		else if (ft_strcmp(doc, line) != 0)
			fl = handle_line(fl, line);
		else if (ft_strcmp(doc, line) == 0)
			break ;
	}
	put_in_file_and_close(fl, file, flag, ft_strlen(fl));
}

void	make_doc(char *doc, int flag)
{
	pid_t	pid;
	int		status;
	char	*name;
	int		file;

	name = get_doc_name();
	file = open(name, O_TRUNC | O_WRONLY | O_APPEND | O_CREAT | O_RDONLY, 0644);
	pid = fork();
	signal (SIGQUIT, SIG_IGN);
	signal (SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal_call(2);
		norm_make_doc(name, doc, flag, file);
		exit(0);
	}
	else
		hd_wait(&status, &pid);
	close(file);
	if (get_status() == 130)
		g_lobal->hd_sig = 130;
	g_lobal->all_fd[g_lobal->fd_index++] = open(name, O_RDONLY);
	free(name);
}
