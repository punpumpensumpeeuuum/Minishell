/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:23:07 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/15 18:00:29 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_input1(t_vars *mini, char ***tudo)
{
	int	i;
	int	status;

	i = 0;
	while (tudo[i])
	{
		free_split(tudo[i]);
		i++;
	}
	free(tudo);
	closeall(mini);
	free(mini->fd);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_code = 128 + WTERMSIG(status);
	}
}

int	checkinput(t_vars *mini)
{
	char	***tudo;

	mini->p = 0;
	mini->trueflag = ft_split(mini->input, '|');
	tudo = paodelosplit(mini->input, numpipe(mini->input), 0);
	if (tudo == NULL || mini->trueflag == NULL)
		return (2);
	fdfd(mini);
	while (mini->p <= numpipe(mini->input) && numpipe(mini->input) >= 0)
	{
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
	free_split(mini->trueflag);
	check_input1(mini, tudo);
	return (0);
}

int	decide(char **str, t_vars *mini)
{
	mini->i = findbuiltimatrix(str, mini);
	if (mini->i == -2)
		mini->i = findcmdinmatrix(str, mini);
	if (mini->i == -1)
	{
		if (findmistake(str) == -1)
			return (3);
		de_codifiqing(str[findmistake(str)]);
		g_exit_code = 127;
		ft_printf("%s: command not found\n", str[findmistake(str)]);
		return (2);
	}
	else if (mini->i == -15)
		return (1);
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
	if (i == 1 || i == 2)
		return ;
	mini->pid = fork();
	if (mini->pid == 0)
	{
		sim = ft_strjoin("/", str[mini->p][mini->i]);
		checkpath(sim, mini, 0);
		nao = findflags(str[mini->p], mini->i);
		cmddd(mini, str, i, nao);
		if (execve(mini->check, nao, mini->env) == -1)
		{
			g_exit_code = 127;
			ft_printf("%s: command not found\n", str[mini->p][mini->i]);
		}
	}
}

void	cmddd(t_vars *mini, char ***str, int i, char **nao)
{
	if (i != 0)
		killchild(str, mini);
	child_signals_handler();
	if (forredirect(str[mini->p], mini) < 0 || forredirectout(str,
			mini) < 0)
		killchild(str, mini);
	if (checkbuiltin(mini) == 0)
		killchild(str, mini);
	if (nao[1] && ft_strncmp(nao[1], "<<", 2) == 0)
	{
		if (nao[1])
			free(nao[1]);
		if (nao[2])
			free(nao[2]);
		nao[1] = ft_strdup("heredoc_tmp.txt");
		nao[2] = NULL;
	}
}
