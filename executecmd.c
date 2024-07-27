/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:08:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/07/03 00:53:29 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arrangepipes(t_vars *mini, int i)
{
	if (!mini->redrct && i == 0)
	{
		// ft_printf("bbbb: %d\n", i + 1);
		ft_printf("bb22: %d\n", mini->fd[i + 1]);
		dup2(mini->fd[i + 1], 1);
		return ;
	}
	else if (!mini->redrct && i < numpipe(mini->input))
	{
		ft_printf("0: %d\n", mini->fd[2 * (i - 1)]);
		ft_printf("1: %d\n", mini->fd[2 * i + 1]);
		dup2(mini->fd[2 * (i - 1)], 0);
		dup2(mini->fd[2 * i + 1], 1);
		return ;
	}
	else if (!mini->redrct && i == numpipe(mini->input))
	{
		// ft_printf("aaa0: %d\n", 2 * (i - 1));
		ft_printf("aaa1: %d\n", mini->fd[2 * (i - 1)]);
		dup2(mini->fd[2 * (i - 1)], 0);
		return ;
	}
}

int	indicateredi(t_vars *mini, int *fd, char *redirection)
{
	int	i;

	i = 0;
	if (mini->flagfdin != 0)
	{
		fd[0] = open(redirection, O_RDONLY);
		if (fd[0] == -1)
			return (ft_printf("%s: No such file or directory\n", redirection));
		dup2(fd[0], 0);
	}
	free(mini->redrct);
	mini->flagfdin = 0;
	while (mini->input[i] && mini->input[i] != '>')
		i++;
	redirect(mini, &mini->input[i]);
	if (mini->flagfdout != 0)
	{
		fd[1] = open(redirection, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(fd[1], 1);
	}
	if (mini->redrct == NULL)
		free(mini->redrct);
	mini->flagfdout = 0;
	return (0);
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
			if (getpipepath(mini->trueflag, mini) == 0)
				return ;
			mini->flagfdin = 0;
			mini->flagfdout = 0;
			veryexecute(mini, i);
			mini->check = NULL;
			ft_printf("2a\n");
			i++;
		}
	}
	else
		executeone(mini);
	waitpid(mini->pid, NULL, 0);
	closeall(mini);
}

void	veryexecute(t_vars *mini, int i)
{
	mini->redrct = NULL;
	mini->pid = fork();
	if (mini->pid == 0)
	{
		redirect(mini, mini->input);
		arrangepipes(mini, i);
		indicateredi(mini, mini->fd, mini->redrct);
		printf("817242a\n");
		if (execve(mini->check, mini->trueflag, mini->env) == -1)
			ft_printf("%s: command not found\n", mini->trueflag[0]);
		printf("555555555555555\n");
		exit(2);
	}
	else
	{
		waitpid(mini->pid, NULL, 0);
		return ;
	}
}

void	executeone(t_vars *mini)
{
	mini->redrct = NULL;
	mini->pid = fork();
	if (mini->pid == 0)
	{
		redirect(mini, mini->input);
		if ((mini->flagfdin != 0 || mini->flagfdout != 0) && \
				indicateredi(mini, mini->fd, mini->redrct) != 0)
			exit(2);
		else
			dup2(mini->fd[1], 1);
		if (execve(mini->check, mini->trueflag, mini->env) == -1)
			ft_printf("aiai||%s: command not found\n", mini->trueflag[0]);
		exit(1);
	}
	else
		return ;
}
