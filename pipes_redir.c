/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:53:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/19 11:42:48 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipinghelp(char ***str, t_vars *mini, int *ta, int o)
{
	if (mini->p == o && !str[mini->p + 1])
	{
		if ((*ta) == 2 || (*ta) == 3)
			return ;
		dup2(mini->fd[2 * (mini->p - 1)], 0);
		if ((*ta) == 1)
			return ;
	}
}

void	piping(char ***str, t_vars *mini, int *ta)
{
	int	o;

	o = numpipe(mini->input);
	if (mini->p == 0 && str[mini->p + 1])
	{
		if ((*ta) == 1 || (*ta) == 3)
			return ;
		dup2(mini->fd[mini->p + 1], 1);
	}
	else if (mini->p > 0 && mini->p < o && str[mini->p + 1])
	{
		if ((*ta) == 3)
			return ;
		if ((*ta) == 2)
			return ;
		dup2(mini->fd[2 * (mini->p - 1)], 0);
		if ((*ta) == 1)
			return ;
		dup2(mini->fd[2 * mini->p + 1], 1);
	}
	else
		pipinghelp(str, mini, ta, o);
	closeall(mini);
}

int	forredirect(char **str, t_vars *mini, int *ta)
{
	int	j;

	j = 0;
	while (str[j] && str[j + 1])
	{
		if (ft_strncmp(str[j + 1], "<<\0", 3) == 0)
		{
			if (setinfile(mini->heredoc_file, mini, 2) == 0)
				return (1);
		}
		else if (ft_strncmp(str[j], "<\0", 2) == 0)
		{
			if (str[j + 1] && access(str[j + 1], R_OK) == 0)
			{
				if (setinfile(str[j + 1], mini, 0) == 0)
				{
					(*ta) += 2;
					return (1);
				}
				else
				{
					ft_printf("%s: No such file or directory\n", str[j + 1]);
					return (-40);
				}
			}
			else
			{
				ft_printf("%s: No such file or directory\n", str[j + 1]);
				return (-20);
			}
		}
		j++;
	}
	return (0);
}

int	forredirectout(char ***str, t_vars *mini, int *ta)
{
	int	j;

	j = 0;
	if (ft_countwords(mini->input, ' ') == 1)
		return (0);
	while (str[mini->p][j])
		j++;
	j--;
	while (j > 0 && str[mini->p][j] && ft_strncmp(str[mini->p][j], ">", 1) != 0)
		j--;
	if (str[mini->p][j] && ft_strncmp(str[mini->p][j], ">>", 2) == 0)
	{
		if (str[mini->p][j + 1])
		{
			if (setinfile(str[mini->p][j + 1], mini, 3) == 0)
				(*ta)++;
			else
				return (-100);
		}
	}
	else if (str[mini->p][j] && ft_strncmp(str[mini->p][j], ">", 1) == 0)
	{
		if (str[mini->p][j + 1])
		{
			if (setinfile(str[mini->p][j + 1], mini, 1) == 0)
				(*ta)++;
			else
				return (-100);
		}
	}
	return (0);
}
