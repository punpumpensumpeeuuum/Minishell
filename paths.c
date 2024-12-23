/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:42:08 by elemesmo          #+#    #+#             */
/*   Updated: 2024/11/15 17:33:30 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freefreefree(char *boas, t_vars *mini)
{
	free(mini->check);
	mini->check = ft_strdup(boas);
	free(boas);
}

void	checkpath(char *cmd, t_vars *mini, int i)
{
	char	*boas;

	if (!mini->input)
		return ;
	boas = ft_strdup(trimtrimtrim(mini->input, 0));
	if (access(boas, X_OK) == 0)
	{
		freefreefree(boas, mini);
		return ;
	}
	if (access(cmd, X_OK) == 0)
	{
		free(mini->check);
		mini->check = ft_strdup(cmd);
		free(boas);
		return ;
	}
	if (mini->check && access(mini->check, X_OK) == 0)
	{
		free(boas);
		return ;
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
