/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:30:31 by ergrigor          #+#    #+#             */
/*   Updated: 2022/12/23 17:34:19 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_env(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
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

int	lex_analyser(t_token *token)
{
	t_token	*ptr;
	int		res;

	ptr = token;
	hd_count = 0;
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
			{
				printf("Error DBQT\n");
				break ;
			}
		}
		else if (ptr->type == SINGLE_QUOTES)
		{
			while (ptr->next && ptr->next->type != SINGLE_QUOTES)
				ptr = ptr->next;
			if (ptr->next && ptr->next->type == SINGLE_QUOTES)
				ptr = ptr->next->next;
			else
			{
				printf("Error SQT\n");
				break ;
			}
		}
		else if (ptr->type == RED_INPUT || ptr->type == RED_OUTPUT
			|| ptr->type == RED_OUTPUT_APP)
		{
			if (ptr->next->type == SPACE_TK)
				ptr = ptr->next;
			if (ptr->next && ptr->next->type == DOUBLE_QUOTES)
			{
				ptr = ptr->next->next;
				while (ptr->next && ptr->next->type != DOUBLE_QUOTES)
					ptr = ptr->next;
				if (ptr == NULL)
				{
					printf("Error REDIRECTION ARG");
					break ;
				}
				else
					printf("Success\n");
				ptr = ptr->next->next;
				// sleep(10);
			}
			else if (ptr->next && ptr->next->type == SINGLE_QUOTES)
			{
				ptr = ptr->next->next;
				while (ptr && ptr->type != SINGLE_QUOTES)
					ptr = ptr->next;
				if (ptr == NULL)
				{
					printf("Error REDIRECTION ARG");
					break ;
				}
				else
					printf("Success\n");
				ptr = ptr->next;
			}
			else if (ptr->next && ptr->next->type == WORD)
			{
				ptr = ptr->next->next;
			}
		}
		else if (ptr->type == WORD)
		{
			ptr = ptr->next;
			printf("Success\n");
		}
		else if (ptr->type == HERE_DOC && hd_maker(ptr) == -1)
			return (-1);
		else if (ptr->type == PIPE)
		{
			ptr = ptr->next;
			if (ptr->type == SPACE_TK)
				ptr = ptr->next;
			if (!ptr || ptr->type == PIPE)
			{
				printf ("PIPE Error\n");
				break ;
			}
			else
				printf("success");
		}
		else// if (ptr->type == SPACE_TK)
		{
			ptr = ptr->next;
		}
		
	}
	return (0);
}

int	main(int argc, char **argv, char **_env)
{
	char		*cmd_line;
	int			status;
	t_env		*env;
	t_token		*tokens;

	env = pars_env(_env);
	while (1)
	{
		cmd_line = readline("Say - Hello myalmo > ");
		if (empty_line(cmd_line) != 1)
			add_history(cmd_line);
		tokens = lexer(cmd_line);
		status = lex_analyser(tokens);
		// if (status == 0)
		// 	printf("xosqi toshnia\n");
		// tokenprint(tokens);
		//print_env(env);
		// lexer(&all_cmd);
	}
	return (0);
}
