/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:54 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/19 17:20:36 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_env_export(t_vars *mini)
{
	if (mini)
	{
		if (mini->env)
		{
			free_array(mini->env);
			mini->env = NULL;
		}
		if (mini->new_env)
		{
			free_array(mini->new_env);
			mini->new_env = NULL;
		}
		free_env_export1(mini);
		free(mini);
	}
}

void	free_env_export1(t_vars *mini)
{
	if (mini->export)
	{
		free_array(mini->export);
		mini->export = NULL;
	}
	if (mini->new_export)
	{
		free_array(mini->new_export);
		mini->new_export = NULL;
	}
	if (mini->check)
		free(mini->check);
	if (mini->input && mini->heredoc_files)
		cleanup_heredoc_files(mini, numpipe(mini->input) + 1);
}

void	killchild(char ***str, t_vars *mini)
{
	int	i;

	i = -1;
	while (str[++i])
		free_split(str[i]);
	free(str);
	free(mini->fd);
	free_split(mini->trueflag);
	free_env_export(mini);
	exit(g_exit_code);
}
