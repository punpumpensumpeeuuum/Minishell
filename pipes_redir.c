/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:53:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/19 17:50:31 by dinda-si         ###   ########.fr       */
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

int	handle_heredoc_redirection(t_vars *mini)
{
	if (setinfile(mini->heredoc_file, mini, 2) == 0)
		return (1);
	return (0);
}

int	handle_input_redirection(char **str, t_vars *mini, int *ta, int j)
{
	if (str[j + 1] && access(str[j + 1], R_OK) == 0)
	{
		if (setinfile(str[j + 1], mini, 0) == 0)
		{
			(*ta) += 2;
			closeall(mini);
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

int	forredirect(char **str, t_vars *mini, int *ta)
{
	int	j;
	int	result;

	j = 0;
	while (str[j] && str[j + 1])
	{
		if (ft_strncmp(str[j + 1], "<<\0", 3) == 0)
		{
			if (handle_heredoc_redirection(mini) == 1)
				return (1);
		}
		else if (ft_strncmp(str[j], "<\0", 2) == 0)
		{
			result = handle_input_redirection(str, mini, ta, j);
			if (result != 0)
				return (result);
		}
		j++;
	}
	return (0);
}
