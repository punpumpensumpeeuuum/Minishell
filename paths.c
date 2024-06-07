/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:42:08 by elemesmo          #+#    #+#             */
/*   Updated: 2024/06/07 00:58:32 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closeall(t_vars *mini)
{
	int	i;

	i = 0;
	while (i < (numpipe(mini->input) + 1) * 2)
	{
		close(mini->fd[i]);
		i++;
	}
}

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

int	getpipepath(char **trueflag, t_vars *mini)
{
	mini->check = checkpath(ft_strjoin("/", trueflag[0]), mini->env);
	if (mini->check != NULL)
		return (1);
	return (0);
}

int	fastcheckpath(t_vars *mini, int flag, int i)
{
	if (flag == 0)
	{
		mini->flag = ft_split(mini->input, ' ');
		mini->trueflag = ft_goodsplit(mini->input);
		mini->check = checkpath(ft_strjoin("/", mini->trueflag[0]), mini->env);
		if (mini->check != NULL)
			return (1);
		return (0);
	}
	else
	{
		mini->flag = ft_split(mini->input, '|');
		while (mini->flag[i])
		{
			mini->trueflag = ft_goodsplit(mini->flag[i]);
			mini->check = checkpath(ft_strjoin("/", \
				mini->trueflag[0]), mini->env);
			if (mini->check != NULL)
				i++;
			else
				return (0);
		}
		return (1);
	}
}
