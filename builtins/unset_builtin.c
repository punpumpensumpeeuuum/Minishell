/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:09:04 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/25 12:06:39 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd_builtin(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_printf("%s\n", pwd);
	free(pwd);
}

char	*get_var(t_vars *mini, char *var)
{
	int		i;
	size_t	var_len;

	if (!var || !mini || !mini->export || !mini->env)
		return (NULL);
	var_len = ft_strlen(var);
	i = 0;
	while (i < mini->exp_len)
	{
		if (mini->export[i] && ft_strncmp(mini->export[i], var, var_len) == 0)
		{
			if (mini->export[i][var_len] == '='
				|| mini->export[i][var_len] == '\0')
				return (mini->export[i]);
		}
		i++;
	}
	return (NULL);
}

int	unsethelp(t_vars *mini, char **split, int i)
{
	char	*str;

	str = get_var(mini, split[i]);
	if (!str)
		return (1);
	env_update(mini, str);
	exp_update(mini, str);
	return (0);
}

void	unset_builtin(t_vars *mini)
{
	char	**split;
	int		i;

	i = 1;
	if (ft_strncmp(mini->trueflag[mini->p], "unset\0", 6) == 0)
		return ;
	split = ft_split(mini->trueflag[mini->p], ' ');
	if (!split)
		return ;
	while (split[i])
	{
		if (unsethelp(mini, split, i) == 1)
		{
			if (!split[i + 1])
			{
				free_split(split);
				return ;
			}
			i++;
			continue ;
		}
		i++;
	}
	free_split(split);
}
