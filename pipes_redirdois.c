/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redirdois.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:53:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/22 18:57:15 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append_redirection(char ***str, t_vars *mini, int *ta, int j)
{
	if (str[mini->p][j + 1])
	{
		if (setinfile(str[mini->p][j + 1], mini, 3) == 0)
		{
			(*ta)++;
			closeall(mini);
			return (0);
		}
		else
		{
			return (-100);
		}
	}
	return (0);
}

int	handle_overwrite_redirection(char ***str, t_vars *mini, int *ta, int j)
{
	if (str[mini->p][j + 1])
	{
		if (setinfile(str[mini->p][j + 1], mini, 1) == 0)
		{
			(*ta)++;
			closeall(mini);
			return (0);
		}
		else
		{
			return (-100);
		}
	}
	return (0);
}

int	forredirectout(char ***str, t_vars *mini, int *ta)
{
	int	j;
	int	result;

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
		result = handle_append_redirection(str, mini, ta, j);
		if (result != 0)
			return (result);
	}
	else if (str[mini->p][j] && ft_strncmp(str[mini->p][j], ">", 1) == 0)
	{
		result = handle_overwrite_redirection(str, mini, ta, j);
		if (result != 0)
			return (result);
	}
	return (0);
}

void	openall(char ***tudo, t_vars *mini)
{
	int	j;
	int	h;

	j = 0;
	if (ft_countwords(mini->input, ' ') == 1)
		return ;
	while (tudo[mini->p][j])
	{
		if (tudo[mini->p][j][0] == '>')
			h = open(tudo[mini->p][j + 1], O_CREAT, 0644);
		j++;
	}
	close(h);
	closeall(mini);
}
