/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ergrigor < ergrigor@student.42yerevan.am > +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:21:19 by ergrigor          #+#    #+#             */
/*   Updated: 2023/01/28 06:58:29 by ergrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	handler(int signal)
{
	if (signal == SIGINT)
	{
		set_status(1);
		g_lobal->signal = 1;
		g_lobal->hd_sig = 1;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_term(int i)
{
	struct termios	gag;

	tcgetattr(0, &gag);
	if (i == 2)
	{
		gag.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &gag);
	}
}

void	signal_call(int i)
{
	if (i == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	if (i == 1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (i == 2)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
	}
}

void	handle_quit(int i)
{
	if (i == SIGQUIT)
	{
		set_status(131);
		g_lobal->signal = 1;
		write(1, "Quit: 3", 8);
		rl_on_new_line();
	}
}