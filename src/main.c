/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:42:37 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/19 19:43:10 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_global	*global;

int	main(int argc, char **argv, char **_env)
{
	struct termios	gago;
	char			*cmd_line;
	int				status;

	//system("leaks checker");
	global = ft_calloc(sizeof(t_global), 1);
	global->env = pars_env(_env);
	// while(1)
	// 	;
	// makefd();
	//print_env(global->env);
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
