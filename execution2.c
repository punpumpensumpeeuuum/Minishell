/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:34:43 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/19 16:50:09 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	countflags(char **str)
{
	int	count;
	int	h;

	count = 0;
	h = 0;
	while (str[h] && ft_strncmp(str[h], ">", 1) != 0)
	{
		if (ft_strncmp(str[h], "<<", 2) != 0)
			count += 2;
		else if (ft_strncmp(str[h], "<", 1) != 0)
			count++;
		h++;
	}
	return (count);
}

char	**allocate_flags_array(char **str, int i, int h, int j)
{
	char	**s;
	int		l;

	l = 0;
	s = malloc(sizeof(char *) * (j + 1));
	if (!s)
		return (NULL);
	s[l++] = ft_strdup(str[i]);
	j = i + 1;
	while (j < h)
	{
		s[l++] = ft_strdup(str[j]);
		j++;
	}
	if (l < h)
		s[l++] = ft_strdup(str[i - 1]);
	s[l] = NULL;
	return (s);
}

char	**findflags(char **str, int i)
{
	int	h;
	int	j;

	j = countflags(str);
	h = 0;
	while (str[h] && ft_strncmp(str[h], ">", 1) != 0)
		h++;
	return (allocate_flags_array(str, i, h, j));
}
