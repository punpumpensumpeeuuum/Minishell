/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:53:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/14 16:12:10 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	piping(char ***str, t_vars *mini, int ta)
{
	int	o;

	o = numpipe(mini->input);
	if (mini->p == 0 && str[mini->p + 1])
	{
		if (ta == 1)
			return ;
		dup2(mini->fd[mini->p + 1], 1);
		closeall(mini);
	}
	else if (mini->p > 0 && mini->p < o && str[mini->p + 1])
	{
		if (ta == 1)
			return ;
		dup2(mini->fd[2 * (mini->p - 1)], 0);
		dup2(mini->fd[2 * mini->p + 1], 1);
		closeall(mini);
	}
	else if (mini->p == o && !str[mini->p + 1])
	{
		if (ta == 1)
			return ;
		dup2(mini->fd[2 * (mini->p - 1)], 0);
		closeall(mini);
	}
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
	{
		mini->fd[1] = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(mini->fd[1], 1);
		close(mini->fd[1]);
	}
	else if (i == 2)
	{
		heredoc(mini);
		mini->fd[0] = open("heredoc_tmp.txt", O_RDONLY);
		if (mini->fd[0] == -1)
		{
			ft_printf("%s: No such file or directory\n", str);
			return (-1);
		}
		dup2(mini->fd[0], 0);
		close(mini->fd[0]);
	}
	else if (i == 3)
	{
		mini->fd[1] = open(str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(mini->fd[1], 1);
		close(mini->fd[1]);
	}
	return (0);
}

int	forredirect(char **str, t_vars *mini)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (ft_strncmp(str[j], "<<\0", 3) == 0)
		{
			if (setinfile(str[j + 1], mini, 2) == 0)
				return (1);
		}
		else if (ft_strncmp(str[j], "<\0", 2) == 0)
		{
			if (str[j + 1] && access(str[j + 1], R_OK) == 0)
			{
				if (setinfile(str[j + 1], mini, 0) == 0)
					return (1);
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
		else
			j++;
	}
	return (0);
}

int	forredirectout(char ***str, t_vars *mini)
{
	int	j;
	int	ta;

	j = 0;
	ta = 0;
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
				ta = 1;
			else
				return (-100);
		}
	}
	else if (str[mini->p][j] && ft_strncmp(str[mini->p][j], ">", 1) == 0)
	{
		if (str[mini->p][j + 1])
		{
			if (setinfile(str[mini->p][j + 1], mini, 1) == 0)
				ta = 1;
			else
				return (-100);
		}
	}
	if (numpipe(mini->input) > 0)
		piping(str, mini, ta);
	return (0);
}
