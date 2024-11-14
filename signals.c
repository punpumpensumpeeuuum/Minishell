/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:13:38 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/13 17:01:37 by dinda-si         ###   ########.fr       */
=======
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:13:38 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/14 16:11:21 by gneto-co         ###   ########.fr       */
>>>>>>> norminette
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*get_mini(void)
{
	static t_vars	mini;

	return (&mini);
}

void	sigint_handler(int sig)
{
	t_vars *mini;
	
	mini = get_mini();
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_code = 130;
	}
}

void	signals_handler(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_heredoc(int sig)
{
	t_vars *mini;
	
	mini = get_mini();
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
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
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
