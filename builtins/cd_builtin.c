/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:45:25 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/27 02:39:36 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_special_1(t_vars *mini)
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
	char	*directory;

	directory = ft_getenv(mini, "HOME");
	if (!directory)
	{
		ft_putstr_fd("minishel: cd: HOME not set", STDERR_FILENO);
		return ;
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
	if (find_flag(split[1]) == 1)
		split[1] = expand(split[1], mini, 0);
	if (split[1] && ft_strncmp(split[1], "-", 1) == 0)
	{
		directory = ft_getenv(mini, "OLDPWD");
		if (!directory)
		{
			ft_putstr_fd("minishel: cd: OLDPWD not set", STDERR_FILENO);
			free_split(split);
			return ;
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

void	atualize_pwd(t_vars *mini, char *var)
{
	int	i;

	i = 0;
	while (i < mini->exp_len)
	{
		if (ft_strncmp(mini->export[i], var, ft_strlen(var)) == 0)
			var = mini->export[i];
		i++;
	}
	i = 0;
	while (i < mini->env_len)
	{
		if (ft_strncmp(mini->export[i], var, ft_strlen(var)) == 0)
		{
			free(mini->env[i]);
			mini->env[i] = ft_strdup(var);
		}
		i++;
	}
}

void	cd_builtin(t_vars *mini)
{
	int	i;

	i = ft_countwords(mini->input, ' ');
	if (i == 1 || cd_special_1(mini) == 0)
		cd_1_arg(mini);
	else if (i == 2)
		cd_2_args(mini);
	else
	{
		ft_putendl_fd("minishell: cd: Too many arguments", STDERR_FILENO);
		return ;
	}
	atualize_pwd(mini, "PWD");
	atualize_pwd(mini, "OLDPWD");
}
