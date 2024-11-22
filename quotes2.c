/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:04:10 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/22 18:04:37 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	preparequotes(t_vars *mini)
{
	int		i;
	char	p;
	int		k;

	i = 0;
	p = '\a';
	k = 0;
	while (mini->input[i])
	{
		if ((mini->input[i] == '\'' || mini->input[i] == '"') && p == '\a')
		{
			k = i;
			p = mini->input[i];
			i++;
		}
		if (p != '\a' && mini->input[i] == 32)
			mini->input[i] = ';';
		if (mini->input[i] == p)
		{
			if (i == k + 1)
			{
				mini->input[i - 1] = ';';
				mini->input[i] = '\0';
			}
			p = '\a';
		}
		i++;
	}
}

void	deprepare(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';')
			str[i] = 32;
		i++;
	}
}

void	depre(t_vars *mini)
{
	int	i;

	i = 0;
	while (mini->trueflag[i])
	{
		de_codifiqing(mini->trueflag[i]);
		deprepare(mini->trueflag[i]);
		i++;
	}
}

void	de(char ***tudo)
{
	int	p;
	int	i;

	p = 0;
	i = 0;
	while (tudo[p])
	{
		while (tudo[p][i])
		{
			de_codifiqing(tudo[p][i]);
			deprepare(tudo[p][i]);
			i++;
		}
		p++;
	}
}
