/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_again.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:34:27 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/13 17:01:43 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	codifiqing(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			j++;
		if (str[i] == '>' && j % 2 != 0)
			str[i] = '\a';
		else if (str[i] == '<' && j % 2 != 0)
			str[i] = '\b';
		else if (str[i] == '|' && j % 2 != 0)
			str[i] = '\t';
		i++;
	}
}

void	de_codifiqing(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			j++;
		if (str[i] == '\a' && j % 2 != 0)
			str[i] = '>';
		else if (str[i] == '\b' && j % 2 != 0)
			str[i] = '<';
		else if (str[i] == '\t' && j % 2 != 0)
			str[i] = '|';
		i++;
	}
}

int		check_quote_redir(t_vars* mini, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			mini->redir++;
			return (0);
		}
		i++;
	}
	return (1);
}

char	*convert_exit_code(void)
{
	char	*converted;
	
	converted = ft_itoa(g_exit_code);
	return (converted);
}
