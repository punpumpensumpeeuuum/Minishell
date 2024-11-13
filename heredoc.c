/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:21:30 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/13 16:46:52 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_dollar_finish(char *str, int k, t_vars *mini)
{
	char	*result;
	char	*real_result;

	result = ft_strdup(str + k);
	real_result = NULL;
	if (!str || !mini || !result)
		return (NULL);
	heredoc_dollar_finish_help(mini, result, str, real_result);
	free(result);
	return (real_result);
}

void	heredoc_dollar_finish_help(t_vars *mini, \
					char *result, char *str, char *real_result)
{
	int		i;
	int		j;
	char	*env_var;

	j = 0;
	i = 0;
	env_var = NULL;
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
			heredoc_dollar_finish1(result, str, real_result);
			free(env_var);
			break ;
		}
		free(env_var);
		i++;
	}
}

void	heredoc_dollar_finish1(char *result, char *str, char *real_result)
{
	int	u;
	int	j;
	int	v;

	u = 0;
	j = 0;
	v = 0;
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
}

int	heredoc(t_vars *mini)
{
	pid_t	pid;
	int		status;
	char	*tmp_filename;
	int		fdin;

	tmp_filename = "heredoc_tmp.txt";
	fdin = open(tmp_filename, O_RDONLY);
	status = 0;
	heredoc_lim_array(mini);
	if (!mini->limiters)
		return (EXIT_FAILURE);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		fork_error();
	else if (pid == 0)
		heredoc_child(mini->limiters, mini);
	return (heredoc1(fdin, status));
}

int	heredoc1(int fdin, int status)
{
	wait(&status);
	signal(SIGINT, sigint_handler);
	if (fdin < 0)
	{
		perror("Error opening temporary file\n");
		return (EXIT_FAILURE);
	}
	dup2(fdin, STDIN_FILENO);
	close(fdin);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	exit_code = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}
