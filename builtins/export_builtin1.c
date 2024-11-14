/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:46:26 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/14 16:05:56 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_update(t_vars *mini, char *str)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	if (!mini->new_export)
	{
		printf("Error: mini->new_export not initialized.\n");
		return ;
	}
	while (i < mini->exp_len)
	{
		if (mini->export[i] && str_compare(mini->export[i], str) == 0)
		{
			free(mini->new_export[i]);
			mini->new_export[i] = ft_strdup(str);
			i++;
			break ;
		}
		else if (!mini->export[i] && done == 0)
		{
			done = 1;
			mini->new_export[i] = ft_strdup(str);
			i++;
			continue ;
		}
		else if (mini->export[i] && str_compare(mini->export[i], str) != 0)
			mini->new_export[i] = ft_strdup(mini->export[i]);
		i++;
	}
	mini->new_export[i] = NULL;
	export_update1(mini);
}

void	export_update1(t_vars *mini)
{
	int		i;
	char	**temp;

	i = 0;
	free_double_array(mini->export, mini->exp_len);
	temp = realloc(mini->export, sizeof(char *) * (mini->exp_len + 1));
	if (!temp)
		return ;
	mini->export = temp;
	while (i < mini->exp_len)
	{
		if (mini->new_export[i])
			mini->export[i] = ft_strdup(mini->new_export[i]);
		else
			mini->export[i] = NULL;
		i++;
	}
	mini->export[i] = NULL;
	sorting_export(mini);
}

void	exp_update(t_vars *mini, char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strjoin("/3/4", str);
	if (!new_str)
		return ;
	while (mini->export[i] && i < mini->exp_len)
	{
		if (mini->export[i] && ft_strncmp(mini->export[i], str,
				ft_strlen(str)) == 0)
		{
			free(mini->export[i]);
			mini->export[i] = ft_strdup(new_str);
			free(new_str);
			return ;
		}
		i++;
	}
	free(new_str);
	mini->export[i] = NULL;
}
