/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:00:57 by gneto-co          #+#    #+#             */
/*   Updated: 2024/11/14 17:00:57 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	antiantiexpand(char *str, int j, t_vars *mini)
{
	j++;
	while (str[j] && str[j] != 5)
	{
		if (str[j] == '$')
			mini->antiexp = 1;
		j++;
	}
}

int	handlequote(char *str, int j, t_vars *mini)
{
	if (str[j] == '\'')
	{
		str[j] = 5;
		antiantiexpand(str, j, mini);
		return (5);
	}
	else
	{
		str[j] = 6;
		return (6);
	}
	return (0);
}

void	countformaloc(char *str, int *a, int j)
{
	while (str[j])
	{
		(*a)++;
		if (str[j] == 5 || str[j] == 6)
			(*a)--;
		j++;
	}
}

char	*removedestroy(char *str, int i, int a, int j)
{
	char	*s;

	j = 0;
	countformaloc(str, &a, j);
	s = malloc(sizeof(char) * (a + 1));
	j = 0;
	while (str[j])
	{
		if (str[j] != 5 && str[j] != 6 && str[j] != 7)
		{
			s[i] = str[j];
			i++;
		}
		j++;
	}
	s[i] = '\0';
	free(str);
	return (s);
}

char	*quotescrazy(char *str, int j, int pq, t_vars *mini)
{
	while (str[j])
	{
		if ((str[j] == '\'' || str[j] == '"') && pq == 0)
			pq = handlequote(str, j, mini);
		if (pq == 5)
		{
			if (str[j] == '\'')
			{
				str[j] = 5;
				pq = 0;
			}
		}
		if (pq == 6)
		{
			if (str[j] == '"')
			{
				str[j] = 6;
				pq = 0;
			}
		}
		j++;
	}
	if (pq != 0)
		return (NULL);
	return (removedestroy(str, 0, 0, j));
}
