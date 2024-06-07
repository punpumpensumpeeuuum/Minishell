/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/07 00:57:50 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkbuiltin(t_vars *mini)
{
	if (ft_strncmp(mini->input, "env\0", 4) == 0)
	{
		env_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(mini->input, "export\0", 7) == 0)
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
	else if (ft_strncmp(mini->input, "exit\0", 5) == 0)
	{
		exit_builtin(mini);
		return (0);
	}
	else
		return (1);
}

int	checkinput(t_vars *mini)
{
	mini->flagfd = 2;
	allocfd(numpipe(mini->input), mini);
	if (checkbuiltin(mini) == 0)
		return (1);
	if (numpipe(mini->input) > 0)
	{
		execute(mini, 0, numpipe(mini->input));
		return (1);
	}
	else if (fastcheckpath(mini, 0, 0) == 1)
	{
		execute(mini, 0, numpipe(mini->input));
		return (1);
	}
	ft_printf("%s: command not found\n", mini->trueflag[0]);
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

// builtins nao funcionao com ' ' a seguir
