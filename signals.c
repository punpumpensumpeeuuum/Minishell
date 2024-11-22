/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:13:38 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/22 11:18:52 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	child_handler(int signal);
void	signals_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "^C\n", 3);
		g_exit_code = 130;
		exit(130);
	}
}

void	child_handler(int signal)
{
	if (signal == SIGINT)
	{
		//write(2, "CHILD\n", 6);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 1);
	return ;
}

void	child_signals_handler(void)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, child_handler);
	return ;
}
