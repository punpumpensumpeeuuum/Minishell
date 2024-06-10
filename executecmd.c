/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:08:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/10 15:52:17 by dinda-si         ###   ########.fr       */
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
	else if (!mini->redrct && i < numpipe(mini->input))
	{
		// ft_printf("0: %d\n", mini->fd[2 * (i - 1)]);
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

void	execute(t_vars *mini, int i, int p)
{
	if (p > 0)
	{
		if (fastcheckpath(mini, 1, 0) == 0)
		{
			ft_printf("%s: command not found\n", mini->trueflag[0]);
			return ;
		}
		while (i <= p)
		{
			ft_printf("1a\n");
			mini->flag = ft_split(mini->input, '|');
			mini->trueflag = ft_goodsplit(mini->flag[i]);
			// ft_printf("TRUEFLAG 1:%s\n", mini->trueflag[0]);
			// ft_printf("TRUEFLAG 2:%s\n", mini->trueflag[1]);
			// ft_printf("TRUEFLAG 3:%s\n", mini->trueflag[2]);
			// ft_printf("TRUEFLAG 4:%s\n", mini->trueflag[3]);
			if (getpipepath(mini->trueflag, mini) == 0)
				return ;
			mini->flagfd = 2;
			veryexecute(mini, i);
			free(mini->check);
			ft_printf("2a\n");
			i++;
		}
	}
	else
		executeone(mini);
	waitpid(mini->pid, NULL, 0);
	free(mini->fd);
}

void	veryexecute(t_vars *mini, int i)
{
	mini->redrct = NULL;
	mini->pid = fork();
	if (mini->pid == 0)
	{
		redirect(mini, mini->input);
		arrangepipes(mini, i);
		indicateredi(mini->flagfd, mini->fd, mini->redrct);
		execve(mini->check, mini->trueflag, mini->env);
		closeall(mini);
		exit(2);
	}
	else
	{
		waitpid(mini->pid, NULL, 0);
		return ;
	}
}

// VER AQUI
void	executeone(t_vars *mini)
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
		execve(mini->check, mini->trueflag, mini->env);
		exit(1);
	}
	else
		return ;
}
