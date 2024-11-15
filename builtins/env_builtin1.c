/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:14:03 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/15 17:21:31 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	envvv_update(t_vars *mini, char *str)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	de_codifiqing_export(str);
	if (!mini->new_env)
	{
		printf("Error: mini->new_env not initialized.\n");
		return ;
	}
	while (i < mini->env_len)
	{
		if (mini->env[i] && str_compare(mini->env[i], str) == 0)
		{
			free(mini->new_env[i]);
			mini->new_env[i] = ft_strdup(str);
			i++;
			break ;
		}
		else if (!mini->env[i] && done == 0)
		{
			done = 1;
			mini->new_env[i] = ft_strdup(str);
			i++;
			continue ;
		}
		else if (mini->env[i] && str_compare(mini->env[i], str) != 0)
		{
			free(mini->new_env[i]);
			mini->new_env[i] = ft_strdup(mini->env[i]);
		}
			
		i++;
	}
	mini->new_env[i] = NULL;
	envvv_update1(mini);
}

void	envvv_update1(t_vars *mini)
{
	int		i;
	char	**temp;

	i = 0;
	free_double_array(mini->env, mini->env_len);
	temp = realloc(mini->env, sizeof(char *) * (mini->env_len + 1));
	if (!temp)
		return ;
	mini->env = temp;
	while (i < mini->env_len)
	{
		if (mini->new_env[i])
			mini->env[i] = ft_strdup(mini->new_env[i]);
		else
			mini->env[i] = NULL;
		i++;
	}
	mini->env[i] = NULL;
}

void	free_first_string(char **arr)
{
	if (!arr)
		return ;
	free(arr[0]);
	free(arr);
}

void	create_env(t_vars *mini)
{
	int		i;
	char	**i_env;
	char	cwd[PATH_MAX];
	char	*pwd;

	i = 0;
	pwd = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	i_env = malloc(sizeof(char *) * 5);
	mini->env = malloc(sizeof(char *) * 6);
	mini->new_env = malloc(sizeof(char *) * 6);
	if (!i_env || !mini->env)
	{
		free(pwd);
		return ;
	}
	i_env[0] = pwd;
	i_env[1] = "PATH=/home/jomendes:/home/jomendes/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:\
	/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
	i_env[2] = "SHLVL=1";
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

void	shlvl_update(t_vars *mini)
{
	int		i;
	char	*shell_level;
	char	*new_shell_level;
	int		increment;
	char	*number;

	i = find_var(mini, "SHLVL");
	if (i == -1)
		return ;
	shell_level = ft_strchr(mini->env[i], '=') + 1;
	increment = ft_atoi(shell_level);
	increment++;
	number = ft_itoa(increment);
	new_shell_level = ft_strjoin("SHLVL=", number);
	if (!new_shell_level)
		return ;
	free(mini->env[i]);
	free(number);
	mini->env[i] = ft_strdup(new_shell_level);
	free(new_shell_level);
}
