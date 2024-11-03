/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 16:13:38 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/02 00:58:38 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sigint_handler(int sig)
{
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void    signals_handler(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}

void    signal_heredoc(int sig)
{
    if (sig == SIGINT)
    {
        write(2, "^C\n", 3);
        exit(130);
    }
}

void    child_handler(int signal)
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

void    child_signals_handler(void)
{
    signal(SIGINT, child_handler);
    signal(SIGQUIT, child_handler);
    return ;
}