/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moreutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:55:42 by elemesmo          #+#    #+#             */
/*   Updated: 2024/06/19 13:27:12 by elemesmo         ###   ########.fr       */
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

int	findcmdinmatrix(char **puzle, t_vars *mini)
{
	int	i;
	int	ver;

	i = 0;
	while (puzle[i])
	{
		ver = findcmdplace(puzle[i], mini);
		if (ver >= 0)
			return (i);
		i++;
	}
	return (0);
}

int	findcmdplace(char *input, t_vars *mini)
{
	char	*word;
	char	*path;
	int		start;
	int		end;

	start = 0;
	while (input[start])
	{
		while (input[start] && !ft_isprint(input[start]))
			start++;
		if (!input[start])
			break ;
		end = start;
		while (input[end] && ft_isprint(input[end]))
			end++;
		word = strndup(input + start, end - start);
		path = ft_strjoin("/", word);
		free(word);
		checkpath(path, mini);
		free(path);
		if (mini->check != NULL)
			return (start);
		start = end;
	}
	return (-1);
}
