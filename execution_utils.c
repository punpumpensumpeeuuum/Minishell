/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:30:38 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/19 10:32:12 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_fail(char ***str, char **nao)
{
	g_exit_code = 127;
	free(str);
	free_split(nao);
	exit(EXIT_FAILURE);
}

void	forking(t_vars *mini)
{
	mini->pid = fork();
	if (mini->pid < 0)
		fork_error();
}

void	waiting(void)
{
	int	status;

	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_code = 128 + WTERMSIG(status);
	}
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

void	if_heredoc(char **nao, t_vars *mini, char ***str)
{
	if (nao[1] && ft_strncmp(nao[1], "<<", 2) == 0)
	{
		free(nao[1]);
		nao[1] = ft_strdup(mini->heredoc_files[mini->p][0]);
		if (!nao[1])
		{
			ft_printf("Error on heredoc filename.\n");
			killchild(str, mini);
			return ;
		}
		if (nao[2])
		{
			free(nao[2]);
			nao[2] = NULL;
		}
	}
}
