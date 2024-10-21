/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/21 16:15:22 by jomendes         ###   ########.fr       */
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
	else if ((ft_strncmp(mini->input, "pwd", 3) == 0))
	{
		pwd_builtin();
		return (0);
	}
	else if ((ft_strncmp(mini->input, "export", 6) == 0))
	{
		export_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(mini->input, "cd", 2) == 0)
	{
		cd_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(mini->input, "echo", 4) == 0)
	{
		echo_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(mini->input, "unset", 5) == 0)
	{
		unset_builtin(mini);
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
	if (check_heredoc(mini) == 0)
	{
		heredoc(mini);
		return (0);
	}
	if (numpipe(mini->input) > 0)
	{
		execute(mini, 0, numpipe(mini->input));
		return (3);
	}
	if (fastcheckpath(mini, 0, 0) == 1)
	{
		printf("\nOLA\n");
		execute(mini, 0, numpipe(mini->input));
		free(mini->check);
		return (4);
	}
	if (inputnum(mini->input) != -1)
	{
		printf("mini->input[findcmdplace(mini->input, mini)] = %s\n", &mini->input[findcmdplace(mini->input, mini)]);
		checkpath(&mini->input[findcmdplace(mini->input, mini)], mini);
		//arrangegoodsplit(mini);
		execute(mini, 0, numpipe(mini->input));
		free(mini->check);
		return (5);
	}
	ft_printf("%s: command not found\n", mini->flag[0]);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_vars	*mini;

	(void)ac;
	(void)av;
	mini = init_mini();
	init_env(env, mini);
	shlvl_update(mini);
	init_export(mini);
	while (1)
	{
		signals_handler();
		mini->input = readline("a espera> ");
		if (ft_strlen(mini->input) > 0)
		{
			add_history(mini->input);
			mini->input = quotescrazy(mini->input);
			if (mini->input == NULL)
				printf ("Quote error\n");
			else
				checkinput(mini);
			free(mini->input);
		}
	}
}
// dois redirects ao memo tempo
// organizar o goodsplit com um swapstrings
// cmds dependetes de input nao cnseguem com pipe
// ver path absoluto aka ./minishell