/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evenmoreutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:13:36 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/13 08:16:07 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkprint(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (ft_isprint(str[i]) == 1)
			a++;
		i++;
	}
	if (a < 1)
		return (2);
	return (0);
}

char	*trimhelp(char *str, int i, int a, int start)
{
	char	*s;

	while (str[i] && ft_isprint(str[i]))
		i++;
	s = malloc(sizeof(char) * (i - start + 3));
	if (!s)
		return (NULL);
	s[0] = '.';
	s[1] = '/';
	while (start < i)
	{
		s[a] = str[start];
		a++;
		start++;
	}
	s[a] = '\0';
	return (s);
}

char	*trimtrimtrim(char *str, int i)
{
	char	*s;
	int		a;
	int		start;

	i = 0;
	a = 2;
	while (str[i] && strncmp(&str[i], "./", 2) != 0)
		i++;
	if (strncmp(&str[i], "./", 2) == 0)
	{
		i += 2;
		start = i;
		s = trimhelp(str, i, a, start);
		if (s != NULL)
			return (s);
	}
	return (str);
}

int	findmistake(char **str)
{
	int	i;

	i = 0;
	if (str[i][0] == '<')
	{
		if (str[2])
			return (2);
		else
			return (-1);
	}
	else
		return (0);
}

int	more(char *input, int i)
{
	while (input[i])
	{
		if (ft_isprint(input[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
