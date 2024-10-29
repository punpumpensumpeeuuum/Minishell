/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moreutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:55:42 by elemesmo          #+#    #+#             */
/*   Updated: 2024/10/29 12:05:31 by dinda-si         ###   ########.fr       */
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

int	findbuiltimatrix(char **str, t_vars *mini)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "<", 1) != 0 && ft_strncmp(str[i], ">", 1) != 0)
		{
			checkbuiltin(str[i], mini);
			if (mini->check != NULL)
				return (i);			
		}
		i++;
	}
	return (-1);
}

int	findcmdinmatrix(char **puzle, t_vars *mini)
{
	int	i;

	i = 0;
	while (puzle[i])
	{
		if (ft_strncmp(puzle[i], "<", 1) != 0 && ft_strncmp(puzle[i], ">", 1) != 0)
		{
			checkpath(ft_strjoin("/", puzle[i]), mini);
			if (mini->check != NULL)
				return (i);			
		}
		i++;
	}
	return (-1);
}

int	findcmdplace(char *input, t_vars *mini)
{
	int	i;

	i = 0;
	while (input[i])
	{
		checkpath(input, mini);
		i++;
	}
	return (-1);
}
