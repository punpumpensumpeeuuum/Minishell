/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:08:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/31 17:45:31 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	indicateredi(int flagfd, int *fd, char *redirection)
{
	if (flagfd == 0)
	{
		fd[0] = open(redirection, O_RDONLY);
		if (fd[0] == -1)
		{
			ft_printf("%s: No such file or directory", redirection);
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
	int p;
	
	p = numpipe(mini->input);
	if (p > 0)
	{
		while (i <= p)
		{
			mini->flag = ft_split(mini->input, '|');
			mini->trueflag = ft_goodsplit(mini->flag[i]);
			mini->flagfd = 2;
			executeone(mini, env);
			i++;
		}
	}
	else
		executeone(mini, env);	
	waitpid(mini->pid, NULL, 0);
	free(mini->fd);
}

void	veryexecute(t_vars *mini, char **env)
{
	mini->redrct = NULL;
	mini->pid = fork();
	if (mini->pid == 0)
	{		
		redirect(mini, mini->input);
		indicateredi(mini->flagfd, mini->fd, mini->redrct);
		execve(mini->check, mini->trueflag, env);
		exit(2);
	}
	else
		return ;
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
