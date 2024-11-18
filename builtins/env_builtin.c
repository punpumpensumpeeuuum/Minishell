/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:12 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/17 20:27:37 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	allocate_env_arrays(t_vars *mini, int len)
{
	mini->env = malloc(sizeof(char *) * (len + 1));
	mini->new_env = calloc(len + 100, sizeof(char *));
	if (!mini->env || !mini->new_env)
	{
		free(mini->env);
		free(mini->new_env);
		return (0);
	}
	mini->env_len = len;
	return (1);
}

int	copy_environment(char **env, t_vars *mini)
{
	int	i;

	i = 0;
	while (i < mini->env_len)
	{
		mini->env[i] = ft_strdup(env[i]);
		if (!mini->env[i])
		{
			while (i > 0)
				free(mini->env[--i]);
			free(mini->env);
			free(mini->new_env);
			return (0);
		}
		i++;
	}
	mini->env[i] = NULL;
	return (1);
}

void	init_env(char **env, t_vars *mini)
{
	int	i;

	i = 0;
	mini->flag_env = 0;
	if (!env || !*env)
	{
		create_env(mini);
		return ;
	}
	while (env[i])
		i++;
	if (!allocate_env_arrays(mini, i))
		return ;
	if (!copy_environment(env, mini))
		return ;
}

void	env_builtin(t_vars *mini)
{
	int	i;

	i = 0;
	while (i < mini->env_len)
	{
		if (mini->env[i] && !(ft_strncmp(mini->env[i], "/3/4", 2) == 0)
			&& !(ft_strncmp(mini->env[i], "_", 1) == 0))
			ft_printf("%s\n", mini->env[i]);
		i++;
	}
}

void	env_update(t_vars *mini, char *str)
{
	int	i;

	i = 0;
	while (i < mini->env_len)
	{
		if (mini->env[i] && ft_strncmp(mini->env[i], str, ft_strlen(str)) == 0)
		{
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("/3/4", str);
		}
		i++;
	}
	mini->env[i] = NULL;
}
