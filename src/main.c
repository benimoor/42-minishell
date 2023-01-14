/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:30:31 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/14 18:46:25 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_global	*global;

void	print_env(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ptr->hidden != 1)
			printf("%s=%s\n", ptr->val_name, ptr->val_value);
		ptr = ptr->next;
	}
}

void	printlen(char *str, int len)
{
	int	i;

	i = 0;
	printf("[");
	while (str[i] && i < len)
		printf("%c", str[i++]);
	printf("]\n");
}

void	tokenprint(t_token *tokens)
{
	t_token	*ptr;

	ptr = tokens;
	printf("--------------------\n");
	while (ptr)
	{
		printf("Token is : ");
		printlen(ptr->str, ptr->len);
		printf("Length is : %d\n", ptr->len);
		printf("Type is : ");
		if (ptr->type == WORD)
			printf("WORD\n");
		else if (ptr->type == PIPE)
			printf("PIPE\n");
		else if (ptr->type == SPACE_TK)
			printf("SPACE\n");
		else if (ptr->type == OR_IF)
			printf("OR_IF\n");
		else if (ptr->type == AND_OR)
			printf("AND_OR\n");
		else if (ptr->type == RED_INPUT)
			printf("RED_INPUT\n");
		else if (ptr->type == RED_OUTPUT)
			printf("RED_OUTPUT\n");
		else if (ptr->type == HERE_DOC)
			printf("HERE_DOC\n");
		else if (ptr->type == RED_OUTPUT_APP)
			printf("RED_OUTPUT_APP\n");
		else if (ptr->type == DOUBLE_QUOTES)
			printf("DOUBLE_QUOTES\n");
		else if (ptr->type == SINGLE_QUOTES)
			printf("SINGLE_QUOTES\n");
		else
			printf("UNDEFIND\n");
		ptr = ptr->next;
	}
	printf("--------------------\n");
}

int	hd_count_check(t_token * token)
{
	int		count;
	int		flag;
	t_token	*ptr;

	count = 0;
	ptr = token;
	while (ptr)
	{
		if (ptr && ptr->type == HERE_DOC)
		{
			if (ptr->next && ptr->next->type == SPACE_TK)
				ptr = ptr->next->next;
			else
				ptr = ptr->next;
			if (!ptr)
				return (count);
			else if (ptr->type == WORD)
			{
				count++;
				ptr = ptr->next;
			}
			else if (ptr->type == DOUBLE_QUOTES || ptr->type == SINGLE_QUOTES)
			{
				flag = ptr->type;
				ptr = ptr->next;
				while (ptr && ptr->type != flag)
					ptr = ptr->next;
				if (!ptr)
					return (count);
				else
					count++;
				ptr = ptr->next;
			}
			else
				return (count);
		}
		else
			ptr = ptr->next;
	}
	return (count);
}

int	lex_analyser(t_token *token)
{
	t_token	*ptr;
	int		res;

	ptr = token;
	global->fd_index = 3;
	global->hd_count = 0;
	if (ptr->type == PIPE || (ptr->type == SPACE_TK
			&& ptr->next && ptr->next->type == PIPE))
		return (set_status(258), ft_putstr_fd("PIPE Error\n", 2), 1);
	if (hd_count_check(ptr) > 16)
		return (ft_putstr_fd("maximum here-document count exceeded\n", 2), 1);
	while (ptr)
	{
		if (ptr->type == DOUBLE_QUOTES)
		{
			ptr = ptr->next;
			while (ptr && ptr->type != DOUBLE_QUOTES)
				ptr = ptr->next;
			if (ptr && ptr->type == DOUBLE_QUOTES)
				ptr = ptr->next;
			else
				return (set_status(258), ft_putstr_fd("Error DBQT\n", 2), 1);
		}
		else if (ptr->type == SINGLE_QUOTES)
		{
			while (ptr->next && ptr->next->type != SINGLE_QUOTES)
				ptr = ptr->next;
			if (ptr->next && ptr->next->type == SINGLE_QUOTES)
				ptr = ptr->next->next;
			else
				return (set_status(258), ft_putstr_fd("Error SQT\n", 2), 1);
		}
		else if (ptr->type == RED_INPUT || ptr->type == RED_OUTPUT
			|| ptr->type == RED_OUTPUT_APP)
		{
			if (make_open(&ptr) != 0)
				return (set_status(1), ft_putstr_fd("Can not open file\n", 2), 1);
		}
		else if (ptr->type == WORD)
		{
			ptr = ptr->next;
		}
		else if (ptr->type == HERE_DOC && hd_maker(ptr) == -1)
			return (set_status(1), 1);
		else if (ptr->type == PIPE)
		{
			ptr = ptr->next;
			if (ptr && ptr->type == SPACE_TK)
				ptr = ptr->next;
			if (!ptr || ptr->type == PIPE)
				return (set_status(258), ft_putstr_fd("PIPE Error\n", 2), 1);
		}
		else if (ptr->type == SPACE_TK)
		{
			ptr = ptr->next;
		}
		else
		{
			//printf("stuc?\n");
			//printf("ptr->type? %d\n", ptr->type);
			ptr = ptr->next;
		}	
	}
	set_status(0);
	return (0);
}

int	main(int argc, char **argv, char **_env)
{
	struct termios	gago;
	char			*cmd_line;
	int				status;

	//system("leaks checker");
	global = ft_calloc(sizeof(t_global), 1);
	global->env = pars_env(_env);
	//makefd();
	rl_catch_signals = 0;
	if (tcgetattr(0, &gago) < 0)
		ft_putstr_fd("Error\n", 2);
	while (1)
	{
		if (tcsetattr(0, TCSANOW, &gago) < 0)
			ft_putstr_fd("Error\n", 2);
		signal_call(1);
		cmd_line = readline("Say - Hello myalmo > ");
		if (cmd_line == NULL)
			return (ft_putstr_fd("exit\n", 1), 1);
		if (empty_line(cmd_line) != 1)
		{
			add_history(cmd_line);
		// print_env(global->env);
			global->tokens = lexer(cmd_line);
			status = lex_analyser(global->tokens);
			//tokenprint(global->tokens);
			if (status == 0)
			{
				make_struct();
			}
			free(cmd_line);
			destroy_struct();
		}
		// // lexer(&all_cmd);
	}
	return (0);
}
