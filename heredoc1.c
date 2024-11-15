/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:33:54 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/15 10:09:45 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_lim_array(t_vars *mini)
{
	int		i;
	char	**split;
	int		j;

	i = 0;
	j = 0;
	mini->total_lim = 0;
	split = ft_split(mini->input, ' ');
	mini->limiters = malloc(sizeof(char *) * (count_limiters(split) + 1));
	if (!mini->limiters)
		return ;
	while (split[i])
	{
		if (ft_strncmp(split[i], "<<", 2) == 0)
			add_limiter(mini, split, &i, &j);
		i++;
	}
	mini->limiters[j] = NULL;
	while (mini->limiters[mini->total_lim])
		mini->total_lim++;
	free_array(split);
}

void	add_limiter(t_vars *mini, char **split, int *i, int *j)
{
	(*i)++;
	mini->limiters[*j] = ft_strdup(split[*i]);
	if (!mini->limiters[*j])
	{
		free_array(mini->limiters);
		free_array(split);
		return ;
	}
	(*j)++;
}

void	heredoc_input(int fd, char **limiters, t_vars *mini)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = readline("> ");
		if (line == NULL || (ft_strcmp(line, limiters[i]) == 0))
		{
			free(line);
			i++;
			if (i == mini->total_lim)
				break ;
			continue ;
		}
		if (dollar_flag_count(line) > 0)
			heredoc_expander(fd, line, mini);
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
}

void	heredoc_child(char **limiters, t_vars *mini)
{
	int		fd;
	char	*tmp_filename;

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
