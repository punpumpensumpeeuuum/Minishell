/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:21:30 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/02 01:03:28 by jomendes         ###   ########.fr       */
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

char	*heredoc_dollar_finish(char *str, int k, t_vars *mini)
{
	int i;
	int j;
	int u;
	int v;
	char *env_var;
	char *result;
	char *real_result;

	j = 0;
	i = 0;
	v = 0;
	u = 0;
	result = ft_strdup(str + k);
	real_result = NULL;
	if (!str || !mini || !result)
		return (NULL);
	while (i < mini->exp_len && mini->export[i])
	{
		env_var = take_equal(mini->export[i]);
		if (env_var && ft_strncmp(result, env_var, ft_strlen(result)) == 0)
		{
			if (ft_strlen(result) == ft_strlen(env_var))
			{
				str = mini->export[i];
				j = 0;
			}
			while (str[j] == result[u] && str[j] != '=' && result[u] != '\0')
			{
				j++;
				u++;
			}
			real_result = malloc(sizeof(char) * ft_strlen(str + j) + 1);
			if (str[j] == '=')
			{
				j++;
				while (str[j] != '\0')
					real_result[v++] = str[j++];
				real_result[v] = '\0';
			}
			free(env_var);
			break;
		}
		free(env_var);
		i++;
	}
	free(result);
	return(real_result);
}

void	heredoc_expander(int fd, char *line, t_vars *mini)
{
	char *str;

	str = heredoc_dollar_finish(line, 1, mini);
	if (!str)
		ft_putchar_fd('\n', fd);
	else
		ft_putendl_fd(str, fd);
	free(str);
	return;
}

void	heredoc_input(int fd, char **limiters, t_vars *mini)
{
	char	*line;
	int		total_lim;
	int		i;

	i = 0;
	total_lim = 0;
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
			heredoc_expander(fd, line, mini);
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

void	fork_error(void)
{
	perror("Error forking\n");
	exit(EXIT_FAILURE);
}

void	heredoc_child(char **limiters, t_vars *mini)
{
	int	fd;
	char *tmp_filename;

	tmp_filename = "heredoc_tmp.txt";
	signal(SIGINT, signal_heredoc);
	fd = open(tmp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("Error creating temporary file\n");
		exit(EXIT_FAILURE);
	}
	heredoc_input(fd, limiters, mini);
	close(fd);
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

int	heredoc(t_vars *mini)
{
	pid_t	pid;
	int		status;
	int		exit_status;
	char	*tmp_filename;
	int		fdin;

	
	tmp_filename = "heredoc_tmp.txt";
	heredoc_lim_array(mini);
	if (!mini->limiters)
		return (EXIT_FAILURE);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		fork_error();
	else if (pid == 0)
		heredoc_child(mini->limiters, mini);
	wait(&status);
	signal(SIGINT, sigint_handler);
	fdin = open(tmp_filename, O_RDONLY);
	if (fdin < 0)
	{
		perror("Error opening temporary file\n");
		return (EXIT_FAILURE);
	}
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	//unlink(tmp_filename);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	exit_status = WEXITSTATUS(status);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		return (exit_status);
	}
	return (EXIT_SUCCESS);
}
