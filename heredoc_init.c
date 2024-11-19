/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:29:01 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/19 14:17:31 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	heredoc_files_helper(int *i, t_vars *mini)
{
	char	*tmp_file;

	mini->heredoc_files[*i] = malloc(sizeof(char *) * 2);
	if (!mini->heredoc_files[*i])
	{
		perror("Not able to allocate heredoc_files[current_pos]\n");
		cleanup_heredoc_files(mini, *i);
		return ;
	}
	tmp_file = get_unique_filename(*i);
	if (!tmp_file)
	{
		perror("Failed to create unique filename\n");
		cleanup_heredoc_files(mini, *i);
		return ;
	}
	mini->heredoc_files[*i][0] = ft_strdup(tmp_file);
	mini->heredoc_files[*i][1] = NULL;
	free(tmp_file);
}

void	init_heredocs(t_vars *mini, int *x_files)
{
	mini->heredoc_files = malloc(sizeof(char **) * (*x_files + 1));
	if (!mini->heredoc_files)
	{
		perror("Not able to alloc heredoc_files\n");
		return ;
	}
}

void	heredoc_files_create(t_vars *mini)
{
	int		x_files;
	int		i;

	i = 0;
	x_files = numpipe(mini->input) + 1;
	init_heredocs(mini, &x_files);
	while (i < x_files)
	{
		heredoc_files_helper(&i, mini);
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

void	cleanup_heredoc_files(t_vars *mini, int x_files)
{
	int	i;
	int j;

	j = 0;
	if (mini->heredoc_files)
	{
		i = 0;
		while (i < x_files)
		{
			while (mini->heredoc_files[j])
			{
				if (mini->heredoc_files[j][0])
				{
					free(mini->heredoc_files[j][0]);
					mini->heredoc_files[j][0] = NULL;
				}
				free(mini->heredoc_files[j]);
				mini->heredoc_files[j] = NULL;
				j++;
			}
			i++;
		}
		free(mini->heredoc_files);
		mini->heredoc_files = NULL;
	}
}
