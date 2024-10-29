/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:21:30 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/29 10:46:17 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_limiters(char **split)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	
	while (split[i])
	{
		if (ft_strncmp(split[i], "<<", 2) == 0)
		{
			if (split[i + 1])
				count++;
		}
		i++;
	}
	return (count);
}

void	heredoc_lim_array(t_vars *mini)
{
	int		i;
	char	**split;
	int		j;

	i = 0;
	j = 0;
	split = ft_split(mini->input, ' ');
	mini->limiters = malloc(sizeof(char *) * (count_limiters(split) + 1));
	if (!mini->limiters)
		return;
	while (split[i])
	{
		if (ft_strncmp(split[i], "<<", 2) == 0)
		{
			i++;
			mini->limiters[j] = ft_strdup(split[i]);
			if (!mini->limiters[j])
			{
				free_array(mini->limiters);
				free_array(split);
				return;
			}
			j++;
		}
		i++;
	}
	mini->limiters[j] = NULL;
	free_array(split);
}

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

void	fork_error(void)
{
	perror("Error forking\n");
	exit(EXIT_FAILURE);
}

void	heredoc_child(int fd[2], char **limiters, t_vars *mini)
{
	close(fd[0]);
	heredoc_input(fd, limiters, mini);
	// close unprotected fds();
	//free_minishell(mini);
	exit(EXIT_SUCCESS);
}

void	creat_pipe(int fd[2])
{
	if (pipe(fd) < 0)
	{
		perror("Error creating pipe\n");
		exit(EXIT_FAILURE);
	}
}

void heredoc_input(int fd[2], char **limiters, t_vars *mini)
{
	char *line;
	int i = 0;
	int total_lim = 0;
	
	while (limiters[total_lim])
		total_lim++;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || (ft_strcmp(line, limiters[i]) == 0))
		{
			free(line);
			i++;
			if (i == total_lim)
				break;
			continue;
		}
		if (dollar_flag_count(line) > 0)
			echo_dollar_finish(line, 1, mini, fd[1]);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]);
}

int heredoc(t_vars *mini)
{
	pid_t pid;
	int fd[2];
	int status;

	if (pipe(fd) < 0)
	{
		perror("Error creating pipe\n");
		return (EXIT_FAILURE);
	}
	heredoc_lim_array(mini);
	if (!mini->limiters)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		fork_error();
	else if (pid == 0)
	{
		close(fd[0]);
		heredoc_input(fd, mini->limiters, mini);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
