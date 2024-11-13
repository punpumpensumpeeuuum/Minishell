/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:45:25 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/13 09:33:16 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cd_special_1(t_vars *mini)
{
	char	**split;
	split = ft_split(mini->input, ' ');
	if (ft_countwords(mini->input, ' ') == 2)
	{
		if (split[1] && ft_strncmp(split[1], "~", 1) == 0)
		{
			free_split(split);
			return (0);
		}
	}
	free_split(split);
	return (-1);
}

void	cd_1_arg(t_vars *mini)
{
	char *directory;
	
	directory = ft_getenv(mini, "HOME");
	if (!directory)
	{
		ft_putstr_fd("minishel: cd: HOME not set", STDERR_FILENO);
		return;
	}
	if (directory)
		in_directory(directory, mini);
	free(directory);
}

void	cd_2_args(t_vars *mini)
{
	char	**split;
	char	*directory;
	
	directory = NULL;
	split = ft_split(mini->input, ' ');
	if (split[1] && ft_strncmp(split[1], "-", 1) == 0)
	{
		directory = ft_getenv(mini, "OLDPWD");
		if (!directory)
		{
			ft_putstr_fd("minishel: cd: OLDPWD not set", STDERR_FILENO);
			free_split(split);
			return;
		}
	}
	else
		directory = ft_strdup(split[1]);
	if (directory)
	{
		in_directory(directory, mini);
		free(directory);
		free_split(split);
	}
}

void	cd_builtin(t_vars *mini)
{
	int i;

	i = ft_countwords(mini->input, ' ');
	if (i == 1 || cd_special_1(mini) == 0)
		cd_1_arg(mini);
	else if (i == 2)
		cd_2_args(mini);
	else
	{
		ft_putendl_fd("minishell: cd: Too many arguments", STDERR_FILENO);
		return;
	}
}