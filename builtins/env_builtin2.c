/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:38:14 by elemesmo          #+#    #+#             */
/*   Updated: 2024/11/21 20:56:55 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_existing_or_add_new(t_vars *mini, char *str, int *i, int *done)
{
	while (*i < mini->env_len)
	{
		if (mini->env[*i] && str_compare(mini->env[*i], str) == 0)
		{
			free(mini->new_env[*i]);
			mini->new_env[*i] = ft_strdup(str);
			(*i)++;
			*done = 1;
			continue ;
		}
		else if (!mini->env[*i] && *done == 0)
		{
			*done = 1;
			mini->new_env[*i] = ft_strdup(str);
			(*i)++;
			continue ;
		}
		else if (mini->env[*i] && str_compare(mini->env[*i], str) != 0)
		{
			free(mini->new_env[*i]);
			mini->new_env[*i] = ft_strdup(mini->env[*i]);
		}
		(*i)++;
	}
}

void	envvv_update(t_vars *mini, char *str)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	de_codifiqing_export(str);
	if (!mini->new_env)
	{
		ft_printf("Error: mini->new_env not initialized.\n");
		return ;
	}
	update_existing_or_add_new(mini, str, &i, &done);
	mini->new_env[i] = NULL;
	envvv_update1(mini);
}
