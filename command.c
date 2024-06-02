/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:38:14 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/02 22:45:06 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wordllllen(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c && s[len] != '<' && s[len] != '>')
		len++;
	return (len);
}

int	checkimportant(char *s)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
			return (n);
		if (s[i] != ' ')
		{
			n++;
			while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
				i++;
		}
		else
			i++;
	}
	return (n);
}

char	**ft_goodsplit(char	*str)
{
	int		i;
	char	**goodflag;
	int		num;
	int		len;

	i = 0;
	if (!str)
		return (0);
	num = checkimportant(str);
	goodflag = malloc(sizeof(char *) * (num + 1));
	if (!goodflag)
		return (0);
	goodflag[num] = NULL;
	while (i < num)
	{
		while (*str == ' ' && *str)
			str++;
		len = wordllllen(str, ' ');
		goodflag[i] = ft_substr(str, 0, len);
		str += len;
		i++;
	}
	return (goodflag);
}
