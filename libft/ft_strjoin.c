/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:09:06 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/09 11:29:40 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*n;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	n = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!n)
		return (0);
	while (s1[i] != '\0')
	{
		n[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		n[i] = s2[j];
		i++;
		j++;
	}
	n[i] = '\0';
	return (n);
}
