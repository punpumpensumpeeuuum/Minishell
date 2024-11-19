/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_infile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:43:00 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/19 11:43:13 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setinfile_helper(char *str, t_vars *mini)
{
	if (!str || access(str, F_OK) != 0)
	{
		ft_printf("%s: Heredoc file not found\n", str);
		return ;
	}
	mini->fd[0] = open(str, O_RDONLY);
	if (mini->fd[0] == -1)
	{
		ft_printf("%s: No such file or directory\n", str);
		return ;
	}
	dup2(mini->fd[0], STDIN_FILENO);
	close(mini->fd[0]);
}

void	sentinfile_opening_trunc(char *str, t_vars *mini)
{
	mini->fd[1] = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	dup2(mini->fd[1], 1);
	close(mini->fd[1]);
}

void	sentinfile_opening_append(char *str, t_vars *mini)
{
	mini->fd[1] = open(str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	dup2(mini->fd[1], 1);
	close(mini->fd[1]);
}

int	setinfile(char *str, t_vars *mini, int i)
{
	if (i == 0)
	{
		mini->fd[0] = open(str, O_RDONLY);
		if (mini->fd[0] == -1)
		{
			ft_printf("%s: No such file or directory\n", str);
			return (-1);
		}
		dup2(mini->fd[0], 0);
		close(mini->fd[0]);
	}
	else if (i == 1)
		sentinfile_opening_trunc(str, mini);
	else if (i == 2)
		setinfile_helper(str, mini);
	else if (i == 3)
		sentinfile_opening_append(str, mini);
	return (0);
}
