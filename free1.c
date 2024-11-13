/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:46:08 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/13 20:06:33 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_array(char **str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
}

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

void	free_fd(int p, t_vars *mini)
{
	int	i;

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

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
