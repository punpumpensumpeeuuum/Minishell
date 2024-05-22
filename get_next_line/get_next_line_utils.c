/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:46:07 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/05 18:34:17 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlengetnextline(const char *str, size_t sn)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (sn == 1)
	{
		while (str[i] && str[i] != '\n')
			i++;
		return (i);
	}
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoingetnextline(char *str1, char *str2)
{
	size_t	i;
	char	*p;

	i = 0;
	if (!str1 && !str2)
		return (NULL);
	p = ft_callocgetnextline(ft_strlengetnextline(str1, 0)
			+ ft_strlengetnextline(str2, 0) + 1, 1);
	if (!p)
		return (NULL);
	while (str1 && *str1 != '\0')
		p[i++] = *str1++;
	while (*str2 != '\n' && *str2 && str2)
		p[i++] = *str2++;
	if (*str2 == '\n')
		p[i++] = '\n';
	p[i] = '\0';
	return (p);
}

void	*ft_callocgetnextline(size_t mem, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = (char *)malloc(mem * size);
	if (!ptr)
		return (0);
	while (i < mem * size)
		ptr[i++] = '\0';
	return (ptr);
}
