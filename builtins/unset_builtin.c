/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:09:04 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/14 20:32:43 by elemesmo         ###   ########.fr       */
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

int	unset_builtin(t_vars *mini)
{
	char	**split;
	char	*str;
	int		i;

	i = 1;
	if (ft_strncmp(mini->trueflag[mini->p], "unset\0", 6) == 0)
		return (1);
	split = ft_split(mini->trueflag[mini->p], ' ');
	if (!split || !split[i])
	{
		printf("No variable to unset.\n");
		free(split);
		return (1);
	}
	while (split[i])
	{
		str = get_var(mini, split[i]);
		if (!str)
		{
			free(split);
			printf("Var not found\n");
			return (1);
		}
		env_update(mini, str);
		exp_update(mini, str);
		i++;
	}
	free_array(split);
	return (0);
}
