/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:54 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/31 16:41:07 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd(int p, t_vars *mini)
{
	int i;

	i = 0;
	if (mini->fd)
	{
		while (i < p)
		{
			close(mini->fd[2 * i]);
			close(mini->fd[2 * i + 1]);
			i++;
		}
		free(mini->fd);
		mini->fd = 0;
	}
}

void	free_array(char **array)
{
	if (!array)
		return;
		
	int	i;
	
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
		// if (mini->fd)
		// 	free_fd(numpipe(mini->input), mini);
		free(mini);
		
	}
}