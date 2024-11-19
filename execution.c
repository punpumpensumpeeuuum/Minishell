/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:23:07 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/19 14:15:17 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_input1(t_vars *mini, char ***tudo)
{
	int	i;

	i = 0;
	if (tudo)
	{
		while (tudo[i])
		{
			free_split(tudo[i]);
			tudo[i] = NULL;
			i++;
		}
		free(tudo);
		tudo = NULL;
	}
	i = 0;
	cleanup_heredoc_files(mini, numberof_heredocs(mini->input) + 1);
	closeall(mini);
	if (mini->fd)
	{
		free(mini->fd);
		mini->fd = NULL;
	}
	waiting();
}

void	check_input_loop(t_vars *mini, char ***tudo)
{
	while (mini->p <= numpipe(mini->input) && numpipe(mini->input) >= 0)
	{
		if (ft_strncmp(tudo[mini->p][0], "<<", 2) == 0 && tudo[mini->p])
			mini->p++;
		if (!tudo[mini->p])
			break ;
		if (mini->check != NULL)
		{
			free(mini->check);
			mini->check = NULL;
		}
		if (tudo[mini->p])
			comandddd(tudo, mini);
		mini->p++;
		usleep(25000);
	}
}

int	checkinput(t_vars *mini)
{
	char	***tudo;

	mini->p = 0;
	mini->trueflag = ft_split(mini->input, '|');
	tudo = paodelosplit(mini->input, numpipe(mini->input));
	if (tudo == NULL || mini->trueflag == NULL)
		return (2);
	if (numberof_heredocs(mini->input) > 0)
		heredoc_files_create(mini);
	mini->p = 0;
	fdfd(mini);
	check_input_loop(mini, tudo);
	free_split(mini->trueflag);
	check_input1(mini, tudo);
	return (0);
}

void	comandddd(char ***str, t_vars *mini)
{
	int		i;
	char	*sim;
	char	**nao;

	if (!str[mini->p] || !mini->trueflag[mini->p])
		return ;
	i = decide(str[mini->p], mini);
	if (i >= 1 && i <= 3)
		return ;
	forking(mini);
	if (ft_strncmp(str[mini->p][0], "<<", 2) == 0)
		return ;
	if (mini->pid == 0)
	{
		child_signals_handler();
		sim = ft_strjoin("/", str[mini->p][mini->i]);
		checkpath(sim, mini, 0);
		nao = findflags(str[mini->p], mini->i);
		cmddd(mini, str, i, nao);
		if (execve(mini->check, nao, mini->env) == -1)
		{
			ft_printf("%s: command not found\n", str[mini->p][mini->i]);
			exec_fail(str, nao);
		}
	}
}

void	cmddd(t_vars *mini, char ***str, int i, char **nao)
{
	int	ta;

	ta = 0;
	if (i != 0)
		killchild(str, mini);
	if (!str[mini->p] || !str[mini->p][0])
	{
		ft_printf("Invalid command or NULL string at position %d\n", mini->p);
		killchild(str, mini);
		return ;
	}
	if (numpipe(mini->input) > 0)
		piping(str, mini, &ta);
	if (forredirect(str[mini->p], mini, &ta) < 0
		|| forredirectout(str, mini, &ta) < 0)
		killchild(str, mini);
	if (checkbuiltin(mini) == 0)
		killchild(str, mini);
	if_heredoc(nao, mini, str);
}
