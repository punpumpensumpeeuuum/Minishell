/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/13 16:50:31 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code;

t_vars	*init_mini(void)
{
	t_vars	*mini;

	mini = malloc(sizeof(t_vars));
	if (!mini)
		return (NULL);
	exit_code = 0;
	mini->redir = 0;
	mini->running = 1;
	mini->env = NULL;
	mini->new_env = NULL;
	mini->export = NULL;
	mini->new_export = NULL;
	mini->fd = NULL;
	mini->check = NULL;
	return (mini);
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
		if (ft_strlen(mini->input) > 0 && antisegfault(mini->input) == 0)
		{
			add_history(mini->input);
			mini->input = antimalucos(mini->input);
			if (mini->input)
			{
				mini->input = expand(mini->input, mini);
				if (mini->input)
				{
					codifiqing(mini->input);
					mini->input = quotescrazy(mini->input);
					
					if (mini->input == NULL)
						printf("Quote error\n");
					else
						checkinput(mini);
				}
			}
		}
		free(mini->input);
	}
	free_env_export(mini);
	return (exit_code);
}
