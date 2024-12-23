/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:40:05 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/28 19:49:34 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == ' ' && str[i + 1] == 'e' && str[i + 2] == 'c' && str[i
					+ 3] == 'h' && str[i + 4] == 'o' && str[i + 5] == ' ')
			|| (str[i] == 'e' && str[i + 1] == 'c' && str[i + 2] == 'h' && str[i
					+ 3] == 'o' && str[i + 4] == ' '))
			return (0);
		i++;
	}
	return (1);
}

int	minipff(char *str, int i, int k)
{
	while (str[i] && str[i] != '|')
	{
		if (ft_isalpha(str[i]))
			k++;
		i++;
	}
	return (k);
}

int	porfavor(char *str, int i, int k)
{
	k = minipff(str, i, k);
	if (k == 0)
		return (1);
	k = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			k = minipff(str, i, k);
			if (k == 0)
				return (1);
			k = 0;
		}
		if (str[i])
			i++;
	}
	return (0);
}

int	tesourinha(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '>' && str[i + 1] == '<')
		{
			ft_printf("bash: syntax error\n");
			return (1);
		}
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				i++;
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (!str[i] || str[i] == '|' || str[i] == '<' || str[i] == '>')
			{
				ft_printf("bash: syntax error\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	antisegfault(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "$?", 2) == 0 || find_echo(str) == 0)
		return (0);
	while (str[i])
	{
		if (ft_isprint(str[i], 0))
			break ;
		i++;
	}
	if (i == ft_strlen(str))
		return (2);
	i = 0;
	if (porfavor(str, 0, 0) != 0 && numpipe(str) > 0)
		return (3);
	if (tesourinha(str, 0) != 0)
		return (4);
	while (str[i])
	{
		if (str[i] != 32 && str[i] != '\'' && str[i] != '"')
			return (0);
		i++;
	}
	return (1);
}
