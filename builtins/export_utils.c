/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:55:53 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/14 16:57:33 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_strings(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sorting_export(t_vars *mini)
{
	int	i;
	int	swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < mini->exp_len - 1 && mini->export[i] && mini->export[i + 1])
		{
			if (ft_strncmp(mini->export[i], mini -> export[i + 1],
					ft_strlen(mini->export[i])) > 0
				&& (ft_strncmp(mini->export[i], "/3/4", 2) != 0))
			{
				swap_strings(&mini->export[i], &mini -> export[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
}

int	export_check(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (1);
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] == '_') || str[i] == '=' || ft_isdigit(str[i])
			|| str[i] == '"' || str[i] == '\'' || str[i] == '/')
			i++;
		else
			return (1);
	}
	remove_double_quote(str);
	remove_single_quote(str);
	return (0);
}

int	str_compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s1[i] != '=' && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if ((s1[i] == '=' || !s1[i]) && (s2[i] == '=' || !s2[i]))
		return (0);
	return (1);
}
