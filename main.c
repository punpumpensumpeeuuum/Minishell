/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/19 15:48:07 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_code;

void	fdfd(t_vars *mini)
{
	int	i;

	i = 0;
	mini->fd = malloc(sizeof(int) * (numpipe(mini->input) + 1) * 2);
	if (!mini->fd)
		return ;
	while (i < numpipe(mini->input) + 1)
	{
		if (pipe(mini->fd + 2 * i) < 0)
			return ;
		i++;
	}
}

t_vars	*init_mini(void)
{
	t_vars	*mini;

	mini = malloc(sizeof(t_vars));
	if (!mini)
		return (NULL);
	g_exit_code = 0;
	mini->redir = 0;
	mini->running = 1;
	mini->env = NULL;
	mini->new_env = NULL;
	mini->export = NULL;
	mini->new_export = NULL;
	mini->fd = NULL;
	mini->check = NULL;
	mini->limiters = NULL;
	mini->heredoc_files = NULL;
	mini->heredoc_file = NULL;
	return (mini);
}

void	minimain(t_vars *mini)
{
	add_history(mini->input);
	if (antisegfault(mini->input) == 0)
	{
		mini->input = antimalucos(mini->input, 0, 0);
		if (mini->input)
		{
			mini->input = expand(mini->input, mini);
			if (mini->input)
			{
				codifiqing(mini->input);
				mini->input = quotescrazy(mini->input, 0, 0, 0);
				if (mini->input == NULL)
					printf("Quote error\n");
				else
					checkinput(mini);
			}
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_vars	*mini;

	(void)ac;
	(void)av;
	mini = init_mini();
	init_env(env, mini);
	init_export(mini);
	shlvl_update(mini);
	while (mini->running)
	{
		signals_handler();
		mini->input = readline(RED "bash> " R);
		if (!mini->input)
			break ;
		if (ft_strlen(mini->input) > 0)
			minimain(mini);
		free(mini->input);
	}
	free_env_export(mini);
	return (g_exit_code);
}
