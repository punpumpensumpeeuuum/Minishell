/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:23:02 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/17 10:37:00 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countwords(char const *s, char c)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (*s != c)
		{
			n++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (n);
}

int	ft_wordlen(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**n;
	int		len;
	int		p;

	i = 0;
	if (!s)
		return (0);
	p = ft_countwords(s, c);
	n = malloc(sizeof(char *) * (p + 1));
	if (!n)
		return (0);
	while (i < p)
	{
		while (*s == c && *s != '\0')
			s++;
		len = ft_wordlen(s, c);
		n[i] = ft_substr(s, 0, len);
		if (!n[i])
			return (0);
		s += len;
		i++;
	}
	n[p] = NULL;
	return (n);
}
