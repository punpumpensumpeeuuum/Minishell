/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:40:05 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/14 16:09:26 by gneto-co         ###   ########.fr       */
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

int	bomdia(char *str, int i)
{
	i--;
	while (str[i])
	{
		if (str[i] != '|')
		{
			while (str[i])
			{
				if (ft_isalpha(str[i]))
					return (1);
				i++;
			}
			return (0);
		}
		i--;
	}
	return (0);
}

int	porfavor(char *str, int i, int k, int a)
{
	while (str[i])
	{
		k = minipff(str, i, k);
		if (k == 0)
			return (1);
		if (str[i] == '|')
		{
			i++;
			k = minipff(str, i, k);
			if (k > 0)
				a++;
			k = 0;
		}
		if (str[i])
			i++;
	}
	k = bomdia(str, ft_strlen(str));
	if (k == 0)
		return (1);
	if (a < numpipe(str))
		return (1);
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
		i++;
	}
	return (0);
}

int	antisegfault(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "$?", 2) == 0)
		return (0);
	while (str[i])
	{
		if (ft_isprint(str[i]))
			break ;
		i++;
	}
	if (i == ft_strlen(str))
		return (2);
	i = 0;
	if (porfavor(str, 0, 0, 1) != 0 && numpipe(str) > 0)
		return (3);
	if (tesourinha(str, 0) != 0)
		return (4);
	while (str[i])
	{
		if (str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}
