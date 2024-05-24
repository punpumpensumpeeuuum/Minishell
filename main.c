/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/24 17:57:37 by dinda-si         ###   ########.fr       */
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
	mini->flagfd = 2;

	if (ft_strchr(mini->input, '<') || ft_strchr(mini->input, '>'))
		redirect(mini);
	// if (ft_strchr(mini->input, '>>') || ft_strchr(mini->input, '<<'))
	mini->flag = ft_split(mini->input, ' ');
	mini->cmdt = ft_strjoin("/", mini->flag[0]);
	mini->check = checkpath(mini->cmdt, env);
	return (1);
}

void	executecmd(t_vars *mini, char **env)
{
	mini->pid = fork();
	if (mini->pid == 0)
	{
		if (mini->flagfd == 0)
		{
			mini->fd[0] = open(mini->redrct, O_RDONLY);
			if (mini->fd[0] == -1)
			{
				ft_printf("%s: No such file or directory", mini->redrct);
				return ;
			}
			dup2(mini->fd[0], 0);
		}
		else if (mini->flagfd == 1)
		{
			mini->fd[1] = open(mini->redrct, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			dup2(mini->fd[1], 1);
		}
		execve(mini->check, mini->flag, env);
	}
	waitpid(mini->pid, NULL, 0);
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
				executecmd(&mini, env);
			else
				ft_printf("%s: command not found\n", mini.input);
		}
	}
}

// mini->flag faz split do input todo
// suposto so fazer split do comando e das flags