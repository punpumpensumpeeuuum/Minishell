/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:23:07 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/18 17:17:32 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_input1(t_vars *mini, char ***tudo)
{
	int	i;
	int	status;

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
	cleanup_heredoc_files(mini, numberof_heredocs(mini->input));
	closeall(mini);
	if (mini->fd)
	{
		free(mini->fd);
		mini->fd = NULL;
	}
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_code = 128 + WTERMSIG(status);
	}
}

int	numberof_heredocs(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
			counter++;
		i++;
	}
	return (counter);
}

void	cleanup_heredoc_files(t_vars *mini, int x_files)
{
	int	i;

	if (mini->heredoc_files)
	{
		i = 0;
		while (i < x_files)
		{
			printf("HELLO GUYS\n");
			if (mini->heredoc_files[i])
			{
				printf("HELLO GUYS\n");
				if (mini->heredoc_files[i][0])
				{
					printf("HELLO GUYS\n");
					free(mini->heredoc_files[i][0]);
					mini->heredoc_files[i][0] = NULL;
				}
				free(mini->heredoc_files[i]);
				mini->heredoc_files[i] = NULL;
			}
			i++;
		}
		free(mini->heredoc_files);
		mini->heredoc_files = NULL;
	}
}

void	heredoc_files_create(t_vars *mini)
{
	int		x_files;
	char	*tmp_file;
	int		i;

	i = 0;
	i = 0;
	x_files = numpipe(mini->input) + 1;
	mini->heredoc_files = malloc(sizeof(char **) * (x_files + 1));
	if (!mini->heredoc_files)
	{
		perror("Not able to alloc heredoc_files\n");
		return ;
	}
	while (i < x_files)
	{
		mini->heredoc_files[i] = malloc(sizeof(char *) * 2);
		if (!mini->heredoc_files[i])
		{
			perror("Not able to allocate heredoc_files[current_pos]\n");
			cleanup_heredoc_files(mini, i);
			return ;
		}
		tmp_file = get_unique_filename(i);
		if (!tmp_file)
		{
			perror("Failed to create unique filename\n");
			cleanup_heredoc_files(mini, i);
			return ;
		}
		mini->heredoc_files[i][0] = ft_strdup(tmp_file);
		mini->heredoc_files[i][1] = NULL;
		free(tmp_file);
		if (numberof_heredocs(mini->trueflag[mini->p]) > 0)
		{
			if (heredoc(mini, i) == -1)
			{
				perror("Failed creating heredoc content\n");
				cleanup_heredoc_files(mini, i);
				return ;
			}
		}
		mini->p++;
		i++;
	}
	mini->heredoc_files[x_files] = NULL;
}

int	checkinput(t_vars *mini)
{
	char	***tudo;

	mini->p = 0;
	mini->trueflag = ft_split(mini->input, '|');
	tudo = paodelosplit(mini->input, numpipe(mini->input), 0);
	if (tudo == NULL || mini->trueflag == NULL)
		return (2);
	if (numberof_heredocs(mini->input) > 0)
		heredoc_files_create(mini);
	mini->p = 0;
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

void	exec_fail(char ***str, char **nao)
{
	g_exit_code = 127;
	free(str);
	free_split(nao);
	exit(EXIT_FAILURE);
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
	if (mini->pid < 0)
		fork_error();
	if (mini->pid == 0)
	{
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
	if (i != 0)
		killchild(str, mini);
	child_signals_handler();
	if (!str[mini->p] || !str[mini->p][0])
	{
		ft_printf("Invalid command or NULL string at position %d\n", mini->p);
		killchild(str, mini);
		return ;
	}
	if (forredirect(str[mini->p], mini) < 0 || forredirectout(str, mini) < 0)
		killchild(str, mini);
	if (checkbuiltin(mini) == 0)
		killchild(str, mini);
	printf("minip = %d\n", mini->p);
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
