/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/02 23:52:38 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocfd(int p, t_vars *mini)
{
	int	i;

	i = 0;
	mini->fd = malloc(sizeof(int) * (p + 1));
	while (i < p)
	{
		if (pipe(mini->fd + 2 * i) < 0)
			return ;
		i++;
	}
}

char	*checkpath(char *cmd1, char **env)
{
	int		i;
	char	**paths;
	char	*path;

	i = 0;
	while (env[i++])
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
	paths = ft_split(&env[i][5], ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd1);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		path = NULL;
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (path);
}

int	checkinput(t_vars *mini, char **env)
{
	// int	i;

	mini->flagfd = 2;
	// i = 0;
	// if (ft_strchr(mini->input, '<') || ft_strchr(mini->input, '>'))
	// 	redirect(mini, mini->input);
	// if (ft_strchr(mini->input, '>>') || ft_strchr(mini->input, '<<'))	
	allocfd(numpipe(mini->input), mini);
	if (numpipe(mini->input) > 0)
	{
		execute(mini, env, 0);
		return (1);
	}
	else if (fastcheckpath(mini, env, 0, 0) == 1)
	{
		execute(mini, env, 0);
		return (1);
	}
	else
		ft_printf("%s: command not found\n", mini->trueflag[0]);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_vars	mini;

	(void)ac;
	(void)av;
	while (1)
	{
		mini.input = readline("a espera> ");
		if (ft_strlen(mini.input) > 0)
		{
			add_history(mini.input);
			checkinput(&mini, env);
		}
	}
}

// mini->flag faz split do input todo
// suposto so fazer split do comando e das flags