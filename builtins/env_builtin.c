/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:12 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/19 18:40:39 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_update1(t_vars *mini)
{
	int i;
	int j;
	char **temp;

	i = 0;
	j = 0;
	while (i < mini->env_len)
	{
		if (mini->env[i])
		{
			free(mini->env[i]);
			mini->env[i] = NULL;
		}
		i++;
	}
	i = 0;
	temp = realloc(mini->env, sizeof(char *) * (mini->env_len + 1));
	if (!temp)
		return;
	mini->env = temp;
	while (j < mini->env_len)
	{
		if (mini->new_env[j])
			mini->env[j] = ft_strdup(mini->new_env[j]);
		else
			mini->env[j] = NULL;
		j++;
	}
	mini->env[j] = NULL;
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

void free_first_string(char **arr)
{
	if (!arr)
		return;
	free(arr[0]);
	free(arr);
}

void	create_env(t_vars *mini)
{
	int i;
	char **i_env;
	char cwd[PATH_MAX];
	char *pwd;

	i = 0;
	pwd =  ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	i_env = malloc(sizeof(char *) * 5);
	mini->env = malloc(sizeof(char *) * 6);
	mini->new_env = malloc(sizeof(char *) * 6);
	if (!i_env || !mini->env)
	{
		free(pwd);
		return;
	}
	i_env[0] = pwd;
	i_env[1] = "PATH=/home/jomendes:/home/jomendes/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:\
	/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
	i_env[2] =  "SHLVL=1";
	i_env[3] = "_=/usr/bin/env";
	while (i < 4)
	{
		mini->env[i] = ft_strdup(i_env[i]);
		i++;
	}
	mini->env_len = i;
	mini->env[i] = NULL;
	free_first_string(i_env);
	mini->flag_env = 1;
}

t_vars 	*init_mini(void)
{
	t_vars *mini = malloc(sizeof(t_vars));
	if (!mini)
		return (NULL);
    mini->env = NULL;
    mini->new_env = NULL;
    mini->export = NULL;
    mini->new_export = NULL;
	mini->fd = NULL;
	mini->check = NULL;
	return (mini);
}

// void	init_env(char **env, t_vars *mini)
// {
// 	int	i;
	
// 	i = 0;
	
// 	mini->flag_env = 0;
// 	if (!*env || !env)
// 	{
// 		create_env(mini);
// 		return;
// 	}
// 	if (env && mini->flag_env == 0)
// 	{	
// 		while (env[i])
// 			i++;
// 		mini->env = malloc(sizeof(char *) * (i + 1));
// 		mini->new_env = malloc(sizeof(char *) * (i + 10));
// 		if (!mini->env || !mini->new_env)
// 		{
// 			free_array(mini->env);
// 			free_array(mini->new_env);
// 			return;
// 		}
// 		mini->env_len = i;
// 		i = 0;
// 		while (i < mini->env_len)
// 		{
// 			mini->env[i] = ft_strdup(env[i]);
// 			if (!mini->env)
// 				mini->env = NULL;
// 			i++;
// 		}
// 		mini->env[i] = NULL;
// 	}
// }

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
	mini->new_env = calloc(i + 10, sizeof(char *));
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
		!(ft_strncmp(mini->env[i], "/3/4", 2) == 0))
			printf("%s\n", mini->env[i]);
		i++;
	}
}

void	shlvl_update(t_vars *mini)
{
	int i;
	char *shell_level;
	char *new_shell_level;
	int increment;
	char *number;

	i = find_var(mini, "SHLVL");
	if (i == -1)
		return;
	shell_level = ft_strchr(mini->env[i], '=') + 1;
	increment = ft_atoi(shell_level);
	increment++;
	number = ft_itoa(increment);
	new_shell_level = ft_strjoin("SHLVL=", number);
	if (!new_shell_level)
		return;
	free(mini->env[i]);
	free(number);
	mini->env[i] = ft_strdup(new_shell_level);
	free(new_shell_level);
}
