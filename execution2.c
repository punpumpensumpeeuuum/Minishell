/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:34:43 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/14 14:11:00 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**findflags(char **str, int i)
{
	char	**s;
	int		h;
	int		j;
	int		l;

	h = 0;
	j = 0;
	while (str[h])
	{
		if (ft_strncmp(str[h], "<", 1) != 0)
			j++;
		if (ft_strncmp(str[h], ">", 1) == 0)
			break ;
		h++;
	}
	l = 0;
	s = malloc(sizeof(char *) * (j + 1));
	if (!s)
		return (NULL);
	s[l] = ft_strdup(str[i]);
	l++;
	j = i + 1;
	while (j < h)
	{
		s[l] = ft_strdup(str[j]);
		l++;
		j++;
	}
	if (l < h)
	{
		s[l] = ft_strdup(str[i - 1]);
		l++;
	}
	s[l] = NULL;
	return (s);
}

