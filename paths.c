/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:42:08 by elemesmo          #+#    #+#             */
/*   Updated: 2024/06/12 01:54:36 by elemesmo         ###   ########.fr       */
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

void	checkpath(char *cmd, t_vars *mini)
{
	int		i;

	i = 0;
	if (access(mini->input, X_OK) == 0)
	{
		// espacos e cenas a seguir ta eaaaaaaaaaasy
		mini->check = ft_strdup(mini->input);
		return ;
	}
	if (access(cmd, X_OK) == 0)
	{
		mini->check = ft_strdup(cmd);
		return ;
	}
	if (access(mini->check, X_OK) == 0)
		return ;
	checkhelp(cmd, mini->env, i, mini);
	return ;
}

void	checkhelp(char *comand, char **env, int i, t_vars *mini)
{
	int	p;

	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			mini->allpaths = ft_split(env[i] + 5, ':');
			p = 0;
			while (mini->allpaths[p])
			{
				mini->check = ft_strjoin(mini->allpaths[p], comand);
				if (access(mini->check, X_OK) == 0)
				{
					free_split(mini->allpaths);
					return ;
				}
				free(mini->check);
				mini->check = NULL;
				p++;
			}
			free_split(mini->allpaths);
		}
		i++;
	}
	return ;
}

int	fastcheckpath(t_vars *mini, int flag, int i)
{
	if (flag == 0)
	{
		mini->flag = ft_split(mini->input, ' ');
		mini->trueflag = ft_goodsplit(mini->input);
		checkpath(ft_strjoin("/", mini->trueflag
			[findcmdinmatrix(mini->trueflag, mini)]), mini);
		if (mini->check != NULL)
			return (1);
	}
	else
	{
		mini->flag = ft_split(mini->input, '|');
		while (mini->flag[i])
		{
			mini->trueflag = ft_goodsplit(mini->flag[i]);
			checkpath(ft_strjoin("/", \
				mini->trueflag[0]), mini);
			if (mini->check != NULL)
				i++;
			else
				return (0);
		}
	}
	return (2);
}
