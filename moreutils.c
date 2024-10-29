/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moreutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:55:42 by elemesmo          #+#    #+#             */
/*   Updated: 2024/10/29 15:12:58 by dinda-si         ###   ########.fr       */
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
		return (2);
	else
		return (0);
}

int	truecheckbuilt(char *str)
{
	if (ft_strncmp(str, "cd", 2) == 0 || ft_strncmp(str, "unset", 5) == 0 || \
		ft_strncmp(str, "exit", 4) == 0)
		return (0);
	else if (ft_strncmp(str, "pwd", 3) == 0 || ft_strncmp(str, "env", 3) == 0 || \
		ft_strncmp(str, "export", 6) == 0 || ft_strncmp(str, "echo", 4) == 0)
		return (1);
	else
		return (-2);
}

int	findbuiltimatrix(char **str, t_vars *mini)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "<", 1) != 0 && ft_strncmp(str[i], ">", 1) != 0)
		{	
			if (truecheckbuilt(str[i]) == 1)
				return (i);	
			else if (truecheckbuilt(str[i]) == 0)
			{
				printf("%s\n", str[i]);
				checkbuiltin(str[i], mini);	
				return (-15);
			}
		}
		i++;
	}
	return (-2);
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
