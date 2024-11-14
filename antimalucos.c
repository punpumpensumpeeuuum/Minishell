/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antimalucos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:47:20 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/14 16:58:26 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '<' || str[i] == '>') && (str[i + 1] == '<' || str[i
				+ 1] == '>') && (str[i + 2] == '<' || str[i + 2] == '>'))
		{
			ft_printf("bash: syntax error\n");
			return (NULL);
		}
		i++;
	}
	return (str);
}

int	spaces(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
				i++;
			a += 2;
		}
		else if (str[i] == '|')
		{
			if (!(str[i - 1] == ' ' && str[i + 1] == ' '))
				a += 2;
		}
		i++;
	}
	return (a);
}

void	antiredirects(char *str, char *s, int *i, int *a)
{
	s[(*a)++] = ' ';
	if (str[*i + 1] == '<' || str[*i + 1] == '>')
	{
		s[(*a)++] = str[(*i)++];
		s[(*a)++] = str[(*i)++];
	}
	else
	{
		s[(*a)++] = str[(*i)++];
	}
	s[(*a)++] = ' ';
}

void	antipipes(char *str, char *s, int *i, int *a)
{
	if (str[*i - 1] == ' ' && str[*i + 1] == ' ')
	{
		s[(*a)++] = str[(*i)++];
	}
	else
	{
		s[(*a)++] = ' ';
		s[(*a)++] = str[(*i)++];
		s[(*a)++] = ' ';
	}
}

char	*antimalucos(char *str, int i, int a)
{
	char	*s;

	if (!syntax(str))
		return (NULL);
	if (find_echo(str) == 0)
		return (str);
	a = spaces(str);
	s = malloc(sizeof(char) * (ft_strlen(str) + a + 1));
	if (!s)
		return (NULL);
	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			antiredirects(str, s, &i, &a);
		else if (str[i] == '|')
			antipipes(str, s, &i, &a);
		else
			s[a++] = str[i++];
	}
	s[a] = '\0';
	free(str);
	return (s);
}
