/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:34:24 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/25 15:48:43 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_helper(t_vars *mini)
{
	mini->export = malloc(sizeof(char *) * (mini->env_len + 1));
	mini->new_export = calloc(mini->env_len + 100, sizeof(char *));
	if (!mini->export || !mini->new_export)
	{
		free(mini->export);
		free(mini->new_export);
		return ;
	}
}

void	init_export(t_vars *mini)
{
	int	i;

	i = 0;
	init_helper(mini);
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
				ft_printf("declare -x %s\n", mini->export[i]);
			i++;
		}
	}
	return (0);
}

void	export_var_helper(t_vars *mini, char **split, int i)
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

void	export_var(t_vars *mini)
{
	int		i;
	char	**split;

	i = 1;
	split = ft_split(mini->trueflag[mini->p], ' ');
	if (!mini->new_export)
		return ;
	de(mini->tudo);
	while (mini->tudo[mini->p][i])
	{
		if (export_check(mini->tudo[mini->p][i]) == 0)
			export_var_helper(mini, mini->tudo[mini->p], i);
		else
			ft_printf("export: %s: not a valid identifier\n", \
					mini->tudo[mini->p][i]);
		i++;
	}
	free_split(split);
}
