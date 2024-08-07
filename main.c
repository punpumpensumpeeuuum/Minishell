/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 22:50:45 by elemesmo          #+#    #+#             */
/*   Updated: 2024/07/01 20:59:38 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	more(char *input, int i)
{
	while (input[i])
	{
		if (ft_isprint(input[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	checkbuiltin(t_vars *mini)
{
	if (!(ft_strncmp(mini->input, "env", 3)) && !(more(mini->input, 3)))
	{
		env_builtin(mini);
		return (0);
	}
	else if (!(ft_strncmp(mini->input, "export", 6)) && !(more(mini->input, 6)))
	{
		init_export(mini);
		export_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(mini->input, "echo\0", 5) == 0)
	{
		echo_builtin(mini);
		return (0);
	}
	else if (!(ft_strncmp(mini->input, "exit", 4)))
	{
		exit_builtin(mini);
		return (0);
	}
	else
		return (1);
}

int	checkinput(t_vars *mini)
{
	mini->flagfdin = 0;
	mini->flagfdout = 0;
	allocfd(numpipe(mini->input), mini);
	if (checkbuiltin(mini) == 0)
		return (2);
	if (numpipe(mini->input) > 0)
	{
		execute(mini, 0, numpipe(mini->input));
		return (3);
	}
	if (fastcheckpath(mini, 0, 0) == 1)
	{
		execute(mini, 0, numpipe(mini->input));
		free(mini->check);
		return (4);
	}
	if (inputnum(mini->input) != -1)
	{
		checkpath(&mini->input[findcmdplace(mini->input, mini)], mini);
		execute(mini, 0, numpipe(mini->input));
		free(mini->check);
		return (5);
	}
	return (ft_printf("%s: command not found\n", mini->flag[0]));
}

int	main(int ac, char **av, char **env)
{
	t_vars	mini;

	(void)ac;
	(void)av;
	init_env(env, &mini);
	while (1)
	{
		mini.input = readline("a espera> ");
		if (ft_strlen(mini.input) > 0)
		{
			add_history(mini.input);
			mini.input = quotescrazy(mini.input, 0, 0);
			if (mini.input == NULL)
				printf("Quote error\n");
			else
				checkinput(&mini);
		}
	}
}

// so pode ser a dicionadio a o historiuico se a mensagem foir diretne da anterior
// organizar o goodsplit com um swapstrings
// cmds dependetes de input nao cnseguem com pipe
// mensagem de erro ta crazy com < > pq nao faco goodsplit =D