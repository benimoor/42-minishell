/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:30:31 by ergrigor          #+#    #+#             */
/*   Updated: 2022/12/21 09:00:11 by ergrigor         ###   ########.fr       */
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

int	main(int argc, char **argv, char **_env)
{
	char		*cmd_line;
	int			*tokenized_line;
	t_env		*env;
	t_token		*tokens;

	env = pars_env(_env);
	while (1)
	{
		cmd_line = readline("Say - Hello myalmo > ");
		if (empty_line(cmd_line) != 1)
			add_history(cmd_line);
		tokens = lexer(cmd_line);
		if (lex_analyser(tokens) == 0)
			printf("xosqi toshnia\n");
		else
			printf("Write own Error function");
		// tokenprint(tokens);
		//print_env(env);
		// lexer(&all_cmd);
	}
	return (0);
}
