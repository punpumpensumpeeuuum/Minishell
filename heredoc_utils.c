/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:18:46 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/18 15:37:18 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	creat_pipe(int fd[2])
{
	if (pipe(fd) < 0)
	{
		perror("Error creating pipe\n");
		exit(EXIT_FAILURE);
	}
}

void	fork_error(void)
{
	perror("Error forking\n");
	exit(EXIT_FAILURE);
}

void	heredoc_expander(int fd, char *line, t_vars *mini)
{
	char	*str;

	str = heredoc_dollar_finish(line, 1, mini);
	if (!str)
		ft_putchar_fd('\n', fd);
	else
		ft_putendl_fd(str, fd);
	free(str);
	return ;
}

int	count_limiters(char **split)
{
	int	count;
	int	i;

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
