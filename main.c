/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/29 17:46:06 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		checkinput(t_vars *mini, char **env)
{
	int	i;
	mini->flagfd = 2;

	i = 0;
	// if (ft_strchr(mini->input, '<') || ft_strchr(mini->input, '>'))
	// 	redirect(mini, mini->input);
	// if (ft_strchr(mini->input, '>>') || ft_strchr(mini->input, '<<'))
	if (numpipe(mini->input) > 0)
		execute(mini, env, i);
	else
	{
		mini->flag = ft_split(mini->input, ' ');
		mini->trueflag = ft_goodsplit(mini->input);
	}
	mini->check = checkpath(ft_strjoin("/", mini->trueflag[0]), env);
	if (mini->check != NULL)
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_vars	mini;
	while (1)
	{
		mini.input = readline("a espera> ");
		if (ft_strlen(mini.input) > 0)
		{
			add_history(mini.input);
			if (checkinput(&mini, env) != 0 && mini.input)
				execute(&mini, env, 0);
			else
			{
				ft_printf("%s: command not found\n", mini.trueflag[0]);
			}
		}
	}
}

// mini->flag faz split do input todo
// suposto so fazer split do comando e das flags