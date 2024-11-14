/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:12 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/13 13:24:08 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_env(char **env, t_vars *mini) 
{
    int i = 0;

    mini->flag_env = 0;
    if (!env || !*env) 
	{
        create_env(mini);
        return;
    }
    while (env[i])
		i++;
    mini->env = malloc(sizeof(char *) * (i + 1));
	mini->new_env = calloc(i + 100, sizeof(char *));
    if (!mini->env || !mini->new_env) 
	{
        free(mini->env);
        free(mini->new_env);
        return;
    }
    mini->env_len = i;
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
            return;
        }
        i++;
    }
    mini->env[i] = NULL;
}

void	env_builtin(t_vars *mini)
{
	int	i;

	i = 0;
	while (i < mini->env_len)
	{
		if (mini->env[i] && \
		!(ft_strncmp(mini->env[i], "/3/4", 2) == 0) && !(ft_strncmp(mini->env[i], "_", 1) == 0))
			printf("%s\n", mini->env[i]);
		i++;
	}
}

void	env_update(t_vars *mini, char *str)
{
	int	i;
	
	i = 0;
	while (i < mini->env_len)
	{
		if (mini->env[i] && 
		ft_strncmp(mini->env[i], str, ft_strlen(str)) == 0)
		{
			free(mini->env[i]);
			mini->env[i] = ft_strjoin("/3/4", str);
		}	
		i++;
	}
	mini->env[i] = NULL;
}
