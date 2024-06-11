/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/11 18:25:23 by dinda-si         ###   ########.fr       */
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

int	findcmdplace(char *input, t_vars *mini)
{
	int		i;
	char	*a;

	i = 0;
	while (input[i])
	{
		if (ft_isalpha(input[i]) == 1)
		{
			a = ft_strjoin("/", &input[i - 1]);
			checkpath(a, mini);
			if (mini->check != NULL)
				return (i - 1);
		}
		i++;
	}
	return (0);
}

int	checkinput(t_vars *mini)
{
	mini->flagfd = 2;
	allocfd(numpipe(mini->input), mini);
	if (checkbuiltin(mini) == 0)
		return (2);
	if (numpipe(mini->input) > 0)
	{
		execute(mini, 0, numpipe(mini->input));
		return (3);
	}
	if (fastcheckpath(mini, 0 , 0) == 1)
	{
		execute(mini, 0, numpipe(mini->input));
		free(mini->check);
		return (4);
	}	
	if (inputnum(mini->input) != -1)
	{
		// o problema ta no fastcheck eu to a usar o checkpath bem o problme e q eu preciso e de usar o fast check
		checkpath(&mini->input[findcmdplace(mini->input, mini)], mini);
		arrangegoodsplit(mini);
		execute(mini, 0, numpipe(mini->input));
		free(mini->check);
		return (5);
	}
	ft_printf("%s: command not found\n", mini->flag[0]);
	return (0);
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
			checkinput(&mini);
		}
	}
}

// organizar o goodsplit com um swapstrings
// cmds dependetes de input nao cnseguem
// ver exectue com reditrect input
// ver path absoluto aka ./minishell