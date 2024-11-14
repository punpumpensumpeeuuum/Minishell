/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:34:24 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/14 16:04:35 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_export(t_vars *mini)
{
	int	i;

	i = 0;
	mini->export = malloc(sizeof(char *) * (mini->env_len + 1));
	mini->new_export = calloc(mini->env_len + 100, sizeof(char *));
	if (!mini->export || !mini->new_export)
	{
		free(mini->export);
		free(mini->new_export);
		return ;
	}
	while (i < mini->env_len)
	{
		if (mini->env[i])
		{
			mini->export[i] = ft_strdup(mini->env[i]);
			if (!mini->export[i])
			{
				while (i > 0)
					free(mini->export[--i]);
				free(mini->export);
				free(mini->new_export);
				return ;
			}
		}
		else
			mini->export[i] = NULL;
		i++;
	}
	mini->export[i] = NULL;
	mini->exp_len = i;
}

int	export_builtin(t_vars *mini)
{
	int	i;

	i = 0;
	sorting_export(mini);
	if (ft_countwords(mini->trueflag[mini->p], ' ') > 1)
		export_var(mini);
	else
	{
		while (i < mini->exp_len)
		{
			if (mini->export[i] && !(ft_strncmp(mini->export[i], "/3/4",
						2) == 0))
				printf("declare -x %s\n", mini->export[i]);
			i++;
		}
	}
	return (0);
}

void	export_var(t_vars *mini)
{
	int		i;
	char	**split;

	i = 1;
	split = ft_split(mini->trueflag[mini->p], ' ');
	if (!mini->new_export)
		return ;
	while (split[i])
	{
		if (export_check(split[i]) == 0)
		{
			if (env_check(split[i]) == 0)
			{
				mini->exp_len += 1;
				mini->env_len += 1;
				export_update(mini, split[i]);
				envvv_update(mini, split[i]);
			}
			else
			{
				mini->exp_len += 1;
				export_update(mini, split[i]);
			}
		}
		else
			printf("export: `%s': not a valid identifier\n", split[i]);
		i++;
	}
	free_split(split);
}

int	env_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}
