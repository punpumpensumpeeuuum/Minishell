/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:51:54 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/19 18:25:13 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd(int p, t_vars *mini)
{
	int i;

	i = 0;
	while (i < p)
	{
		close(mini->fd[2 * i]);
		close(mini->fd[2 * i + 1]);
		i++;
	}
	free(mini->fd);
	mini->fd = NULL;
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
			printf("test1\n");
		}
		if (mini->new_env)
		{
			free_array(mini->new_env);
			mini->new_env = NULL;
			printf("test2\n");
		}
		if (mini->export)
		{
			free_array(mini->export);
			mini->export = NULL;
			printf("test3\n"); 
		}
		if (mini->new_export)
		{
			free_array(mini->new_export);
			mini->new_export = NULL;
			printf("test4\n");
		}
		if (mini->fd)
			free_fd(numpipe(mini->input), mini);
		printf("test5\n");
	}
}