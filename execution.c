/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:23:07 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/13 16:47:47 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkinput(t_vars *mini)
{
	char	***tudo;
	int		i;
	int		status;

	mini->p = 0;
	mini->trueflag = ft_split(mini->input, '|');
	tudo = paodelosplit(mini->input, numpipe(mini->input));
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
	}
	i = 0;
	while (tudo[i++])
		free_split(tudo[i]);
	free(tudo);
	closeall(mini);
	free(mini->fd);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
	}
	return (0);
}

void	fdfd(t_vars *mini)
{
	int	i;

	i = 0;
	mini->fd = malloc(sizeof(int) * (numpipe(mini->input) + 1) * 2);
	if (!mini->fd)
		return ;
	while (i < numpipe(mini->input) + 1)
	{
		if (pipe(mini->fd + 2 * i) < 0)
			return ;
		i++;
	}
}

char	***paodelosplit(char *str, int pipes)
{
	int		i;
	int		j;
	char	***res;
	char	**a;
	char	**b;

	i = 0;
	j = 0;
	res = malloc(sizeof(char **) * (pipes + 2));
	a = ft_split(str, '|');
	if (!a)
	{
		free_split(a);
		return (NULL);
	}
	while (j <= pipes)
	{
		b = ft_split(a[j], ' ');
		if (!b)
		{
			free_split(b);
			return (NULL);
		}
		res[j] = malloc(sizeof(char *) * (ft_countwords(a[j], ' ') + 1));
		if (!res[j])
		{
			free_split(a);
			free_split(b);
			free(res);
			return (NULL);
		}
		while (i < ft_countwords(a[j], ' '))
		{
			res[j][i] = ft_strdup(b[i]);
			i++;
		}
		res[j][i] = NULL;
		j++;
		i = 0;
		free_split(b);
	}
	free_split(a);
	res[j] = NULL;
	return (res);
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
		exit_code = 127;
		ft_printf("%s: command not found\n", str[findmistake(str)]);
		return (2);
	}
	else if (mini->i == -15)
		return (1);
	return (0);
}

void	comandddd(char ***str, t_vars *mini)
{
	char	*sim;
	char	**nao;
	int		i;

	if (!str[mini->p] || !mini->trueflag[mini->p])
		return ;
	i = decide(str[mini->p], mini);
	if (i == 1 || i == 2)
		return ;
	mini->pid = fork();
	if (mini->pid == 0)
	{
		if (i != 0)
			killchild(str, mini);
		child_signals_handler();
		if (forredirect(str[mini->p], mini) < 0 || \
		forredirectout(str, mini) < 0)
			killchild(str, mini);
		if (checkbuiltin(mini) == 0)
			killchild(str, mini);
		sim = ft_strjoin("/", str[mini->p][mini->i]);
		checkpath(sim, mini);
		nao = findflags(str[mini->p], mini->i);
		if (nao[1] && ft_strncmp(nao[1], "<<", 2) == 0)
		{
			free(nao[1]);
			free(nao[2]);
			nao[1] = ft_strdup("heredoc_tmp.txt");
			nao[2] = NULL;
		}
		if (execve(mini->check, nao, mini->env) == -1)
		{
			exit_code = 127;
			ft_printf("%s: command not found\n", str[mini->p][mini->i]);
		}
	}
}
