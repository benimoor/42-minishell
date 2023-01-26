/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:42:37 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/26 18:42:29 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_global	*g_lobal;

void	makefd(void)
{
	g_lobal->fd_index = 3;
	g_lobal->all_fd[0] = dup(0);
	g_lobal->all_fd[1] = dup(1);
	g_lobal->all_fd[2] = dup(2);
}

int	mshloop(struct termios *gago, char *cmd_line, int status)
{
	while (1)
	{
		if (tcsetattr(0, TCSANOW, gago) < 0)
			ft_putstr_fd("Error\n", 2);
		signal_call(1);
		cmd_line = readline("[KARGIN-Shell]$. ");
		if (cmd_line == NULL)
			return (ft_putstr_fd("exit\n", 1), 1);
		if (empty_line(cmd_line) != 1)
		{
			add_history(cmd_line);
			g_lobal->tokens = lexer(cmd_line);
			status = lex_analyser(g_lobal->tokens);
			if (status == 0)
			{
				make_struct();
				execution();
			}
			free(cmd_line);
			destroy_struct();
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **_env)
{
	struct termios	gago;
	char			*cmd_line;
	int				status;

	(void)argc;
	(void)argv;
	g_lobal = ft_calloc(sizeof(t_global), 1);
	g_lobal->env = pars_env(_env);
	g_lobal->real_env = _env;
	makefd();
	cmd_line = NULL;
	status = 0;
	rl_catch_signals = 0;
	if (tcgetattr(0, &gago) < 0)
		ft_putstr_fd("Error\n", 2);
	return (mshloop(&gago, cmd_line, status));
}
