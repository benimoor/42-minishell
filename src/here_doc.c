/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:05:55 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 18:07:35 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

void	make_doc(char *doc, int flag)
{
	pid_t	pid;
	int		status;
	char	*line;
	char	*name;
	int		file;

	signal (SIGQUIT, SIG_IGN);
	signal (SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal_call(2);
		name = get_doc_name();
		file = open(name, O_TRUNC | O_WRONLY | O_APPEND | O_CREAT, 0644);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				set_status(1);
				exit(1);
			}
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
		hd_wait(&status, &pid);
	}
}

char	*make_doc_name(t_token *token, int *flag)
{
	char	*res;
	int		flag1;
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
