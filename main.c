/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/22 18:01:11 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executecmd(t_vars *mini, char **env)
{
	mini->pid = fork();
	if (mini->pid == 0)
		execve(mini->check, mini->flag, env);
	waitpid(mini->pid, NULL, 0);
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

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_vars	mini;
	while (1)
	{
		mini.input = readline("a espera> ");
		if (ft_strlen(mini.input) > 0)
			add_history(mini.input);
		mini.flag = ft_split(mini.input, ' ');
		mini.cmdt = ft_strjoin("/", mini.flag[0]);
		mini.check = checkpath(mini.cmdt, env);
		if (mini.check)
		{
			// ft_printf("%s\n", mini.input);
			// ft_printf("%s\n", mini.check);
			executecmd(&mini, env);
		}
		else
			ft_printf("esse comando ta errado\n");
	}
}
