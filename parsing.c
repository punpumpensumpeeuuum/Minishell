/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:40:05 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/12 17:49:51 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == ' ' && str[i + 1] == 'e' && str[i + 2] == 'c' &&
		str[i + 3] == 'h' && str[i + 4] == 'o' && str[i + 5] == ' ') ||
		(str[i] == 'e' && str[i + 1] == 'c' &&
		str[i + 2] == 'h' && str[i + 3] == 'o' && str[i + 4] == ' '))
			return (0);
		i++;
	}
	return (1);
}

char	*antimalucos(char *str)
{
	int		i;
	int		a;
	char	*s;

	a = 0;
	i = 0;
	if (find_echo(str) == 0)
		return (str);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
			{
				if (str[i + 2] == '<' || str[i + 2] == '>')
					return (NULL);
				i ++;
			}
			a += 2;
		}
		if (str[i] == '|')
		{
			if (str[i - 1] == ' ' && str[i + 1] == ' ')
			{	
				i++;
			}	
			else
				a += 2;
		}
		i++;
	}
	s = malloc(sizeof(char) * (i + a + 1));
	if (!s)
		return (NULL);
	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			s[a] = ' ';
			a++;
			if (str[i + 1] == '<' || str[i + 1] == '>')
			{
				s[a] = str[i];
				i++;
				a++;
				s[a] = str[i];
				i++;
				a++;
				s[a] = ' ';
				a++;
			}
			else
			{
				s[a] = str[i];
				a++;
				i++;
				s[a] = ' ';
				a++;				
			}

		}
		if (str[i] == '|')
		{
			if (str[i - 1] == ' ' && str[i + 1] == ' ')
			{		
				s[a] = str[i];
				a++;
				i++;
			}
			else
			{
				s[a] = ' ';
				a++;
				s[a] = str[i];
				a++;
				i++;
				s[a] = ' ';
				a++;
			}

		}
		s[a] = str[i];
		i++;
		a++;
	}
	s[a] = '\0';
	free(str);
	return (s);
}

int porfavor(char *str)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] && str[i] != '|')
			{
				if (ft_isalpha(str[i]))
					k++;
				i++;
			}
			if (k > 0)
				return (0);
		}
		i++;
	}
	return (1);
}

int antisegfault(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			break ;
		i++;
	}
	if (i == ft_strlen(str))
		return (2);
	i = 0;
	if (porfavor(str) != 0 && numpipe(str) > 0)
		return (3);
	while (str[i])
	{
		if (str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}
