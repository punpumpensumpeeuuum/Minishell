/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:21:30 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/25 00:24:20 by elemesmo         ###   ########.fr       */
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
	heredoc_dollar_finish_help(mini, result, str, &real_result);
	free(result);
	return (real_result);
}

void	heredoc_dollar_finish_help(t_vars *mini, char *result, char *str,
		char **real_result)
{
	int		i;
	char	*env_var;

	i = 0;
	env_var = NULL;
	while (i < mini->exp_len && mini->export[i])
	{
		env_var = take_equal(mini->export[i]);
		if (env_var && ft_strncmp(result, env_var, ft_strlen(env_var)) == 0 && \
			ft_strncmp(result, env_var, ft_strlen(result)) == 0)
		{
			if (ft_strlen(result) == ft_strlen(env_var))
				str = mini->export[i];
			heredoc_dollar_finish1(result, str, real_result);
			free(env_var);
			break ;
		}
		free(env_var);
		i++;
	}
}

char	*heredoc_dollar_finish1(char *result, char *str, char **real_result)
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
	*real_result = malloc(sizeof(char) * ft_strlen(str + j) + 1);
	if (!*real_result)
		return (NULL);
	if (str[j] == '=')
	{
		j++;
		while (str[j] != '\0')
			(*real_result)[v++] = str[j++];
		(*real_result)[v] = '\0';
	}
	return (*real_result);
}

int	heredoc(t_vars *mini, int i)
{
	pid_t	pid;
	int		status;
	char	*tmp_filename;

	tmp_filename = mini->heredoc_files[i][0];
	if (!tmp_filename)
		return (EXIT_FAILURE);
	mini->heredoc_file = tmp_filename;
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
	free_split(mini->limiters);
	mini->limiters = NULL;
	return (heredoc1(tmp_filename, status));
}

int	heredoc1(char	*filename, int status)
{
	int	fdin;

	fdin = open(filename, O_RDONLY);
	if (fdin < 0)
		return (EXIT_FAILURE);
	wait(&status);
	signal(SIGINT, sigint_handler);
	close(fdin);
	if (WIFEXITED(status) && WEXITSTATUS(status) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	g_exit_code = WEXITSTATUS(status);
	return (EXIT_SUCCESS);
}
