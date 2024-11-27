/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/27 02:45:22 by elemesmo         ###   ########.fr       */
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
	mini->j = 0;
	mini->nq = 0;
	mini->pq = 0;
	mini->q = '\0';
	mini->env = NULL;
	mini->new_env = NULL;
	mini->export = NULL;
	mini->new_export = NULL;
	mini->tudo = NULL;
	mini->fd = NULL;
	mini->check = NULL;
	mini->limiters = NULL;
	mini->heredoc_files = NULL;
	mini->heredoc_file = NULL;
	mini->antiexp = 0;
	mini->golo = 0;
	return (mini);
}

void	minimain(t_vars *mini)
{
	add_history(mini->input);
	mini->golo = 0;
	if (antisegfault(mini->input) == 0)
	{
		mini->input = antimalucos(mini->input, 0, 0);
		codifiqing(mini->input);
		if (mini->input)
		{
			preparequotes(mini);
			if (find_flag(mini->input) == 1
				&& find_echo(mini->input) == 1)
				mini->input = expand(mini->input, mini, 0);
			if (mini->input == NULL)
				ft_printf("Quote error\n");
			else
				checkinput(mini);
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
		mini->input = readline("bash> ");
		if (!mini->input)
			break ;
		if (ft_strlen(mini->input) > 0)
			minimain(mini);
		if (mini->input != NULL)
		{
			free(mini->input);
			mini->input = NULL;
		}
	}
	free_env_export(mini);
	return (g_exit_code);
}

// cd precisa de expand
// double quotes sao null
// export precisa de ':'
// ctrl C double pronpt
