/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:08:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/29 17:48:59 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	indicatefd(int flagfd, int fd[2], char *redirection)
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
	if (numpipe(mini->input) > 0)
	{
		while (i <= numpipe(mini->input))
		{
			mini->flag = ft_split(mini->input, '|');
			mini->trueflag = ft_goodsplit(mini->flag[i]);
			mini->flagfd = 2;
			redirect(mini, mini->flag[i]);
			// if (mini->redrct == NULL)
			// 	mini->flagfd == 2;
			executeone(mini, env);
			i++;
		}
	}
	else
		executeone(mini, env);
}

void	executeone(t_vars *mini, char **env)
{
	mini->pid = fork();
	if (mini->pid == 0)
	{
		// ft_printf("%d\n", mini->flagfd);
		// ft_printf("%s\n", mini->redrct);
		// ft_printf("%s\n", mini->check);
		// ft_printf("%s\n", mini->trueflag[0]);
		// ft_printf("%s\n", mini->trueflag[1]);
		indicatefd(mini->flagfd, mini->fd, mini->redrct);
		execve(mini->check, mini->trueflag, env);
	}
	waitpid(mini->pid, NULL, 0);
}
