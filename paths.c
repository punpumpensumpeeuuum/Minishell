/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:42:08 by elemesmo          #+#    #+#             */
/*   Updated: 2024/10/30 17:17:36 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	closeall(t_vars *mini)
{
	int	i;

	i = 0;
	while (i < (numpipe(mini->input) + 1) * 2 && mini->fd[i])
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
	if (!mini->fd)
		return;
	while (i < p)
	{
		if (pipe(mini->fd + 2 * i) < 0)
			return;
		i++;
	}
}

void	checkpath(char *cmd, t_vars *mini)
{
	int		i;
	char	*boas;

	i = 0;
	if (!mini->input)
		return;
	boas = ft_strdup(trimtrimtrim(mini->input, 0));
	if (access(boas, X_OK) == 0)
	{
		free(mini->check);
		mini->check = ft_strdup(boas);
		free(boas);
		return;
	}
	if (access(cmd, X_OK) == 0)
	{
		free(mini->check);
		mini->check = ft_strdup(cmd);
		free(boas);
		return;
	}
	if (mini->check && access(mini->check, X_OK) == 0)
	{
		free(boas);
		return;
	}
	free(boas);
	checkhelp(cmd, mini->env, i, mini);
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
	char *joined;

	if (flag == 0)
	{
		mini->flag = ft_split(mini->input, ' ');
		mini->trueflag = ft_goodsplit(mini->input);
		joined = ft_strjoin("/", mini->trueflag
			[findcmdinmatrix(mini->trueflag, mini)]);
		checkpath(joined, mini);
		free(joined);
		if (mini->check != NULL)
			return (1);
			
	}
	else
	{
		mini->flag = ft_split(mini->input, '|');
		while (mini->flag[i])
		{
			joined = ft_strjoin("/", \
				mini->trueflag[0]);
			mini->trueflag = ft_goodsplit(mini->flag[i]);
			checkpath(joined, mini);
			free(joined);
			if (mini->check != NULL)
				i++;
			else
				return (0);
		}
	}
	return (2);
}