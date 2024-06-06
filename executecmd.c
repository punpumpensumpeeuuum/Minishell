/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:08:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/06 17:10:31 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arrangepipes(t_vars *mini, int i)
{
	if (!mini->redrct && i == 0)
	{
		// ft_printf("bbbb: %d\n", i + 1);
		// ft_printf("bb22: %d\n", mini->fd[i + 1]);
		dup2(mini->fd[i + 1], 1);
		return ;
	}
	if (!mini->redrct && i < numpipe(mini->input))
	{
		// ft_printf("0: %d\n", 2 * i - 1);
		// ft_printf("1: %d\n", mini->fd[2 * i + 1]);
		dup2(mini->fd[2 * (i - 1)], 0);
		dup2(mini->fd[2 * i + 1], 1);
		return ;
	}
	else if (!mini->redrct && i == numpipe(mini->input))
	{
		// ft_printf("aaa0: %d\n", 2 * (i - 1));
		// ft_printf("aaa1: %d\n", mini->fd[2 * (i - 1)]);
		dup2(mini->fd[2 * (i - 1)], 0);
		return ;
	}
}

void	indicateredi(int flagfd, int *fd, char *redirection)
{
	if (flagfd == 0)
	{
		fd[0] = open(redirection, O_RDONLY);
		if (fd[0] == -1)
		{
			// ft_printf("%s: No such file or directory", redirection);
			return ;
		}
		dup2(fd[0], 0);
	}
	else if (flagfd == 1)
	{
		fd[1] = open(redirection, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd[1], 1);
	}
}

void	execute(t_vars *mini, char **env, int i)
{
	int	p;

	p = numpipe(mini->input);
	if (p > 0)
	{
		if (fastcheckpath(mini, env, 1, 0) == 0)
		{
			// ft_printf("%s: command not found\n", mini->trueflag[0]);
			return ;
		}
		while (i <= p)
		{
			// ft_printf("1a\n");
			mini->flag = ft_split(mini->input, '|');
			mini->trueflag = ft_goodsplit(mini->flag[i]);
			mini->flagfd = 2;
			veryexecute(mini, env, i);
			i++;
		}
	}
	else
		executeone(mini, env);
	waitpid(mini->pid, NULL, 0);
	free(mini->fd);
}

void	veryexecute(t_vars *mini, char **env, int i)
{
	mini->redrct = NULL;
	mini->pid = fork();
	if (mini->pid == 0)
	{
		int li = 0;
		while (mini->fd[li])
		{
			ft_printf("fd: %d\n", mini->fd[li]);
			ft_printf("i:  %d\n", li);
			li++;
		}
		// ft_printf("IMPORTATNTE: %d\n", mini->pid);
		redirect(mini, mini->input);
		// ft_printf("mmmm\n");
		arrangepipes(mini, i);
		// ft_printf("mmnnnnnmm\n");
		indicateredi(mini->flagfd, mini->fd, mini->redrct);
		execve(mini->check, mini->trueflag, env);
		exit(2);
	}
	else
	{
		waitpid(mini->pid, NULL, 0);
		return ;
	}
}

void	executeone(t_vars *mini, char **env)
{
	mini->redrct = NULL;
	mini->pid = fork();
	if (mini->pid == 0)
	{
		redirect(mini, mini->input);
		if (mini->flagfd != 2)
			indicateredi(mini->flagfd, mini->fd, mini->redrct);
		else
			dup2(mini->fd[1], 1);
		execve(mini->check, mini->trueflag, env);
		exit(1);
	}
	else
		return ;
}
