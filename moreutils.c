/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moreutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:55:42 by elemesmo          #+#    #+#             */
/*   Updated: 2024/11/11 22:16:40 by jomendes         ###   ########.fr       */
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

int	truecheckbuilt(char *str)
{
	if (ft_strncmp(str, "cd\0", 3) == 0 || ft_strncmp(str, "unset\0", 6) == 0 || \
		ft_strncmp(str, "exit\0", 5) == 0 || ft_strncmp(str, "export\0", 7) == 0)
		return (0);
	else if (ft_strncmp(str, "pwd\0", 4) == 0 || ft_strncmp(str, "env\0", 4) == 0 || \
		ft_strncmp(str, "echo\0", 5) == 0)
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
				checkbuiltin(mini);	
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
	char *str;

	i = 0;
	while (puzle[i])
	{
		str = ft_strjoin("/", puzle[i]);
		if (ft_strncmp(puzle[i], "<", 1) != 0 && ft_strncmp(puzle[i], ">", 1) != 0)
		{
			checkpath(str, mini);
			if (mini->check != NULL)
			{
				free(str);
				return (i);
			}			
		}
		i++;
	}
	free(str);
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
