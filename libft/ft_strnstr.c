/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:37:46 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/20 11:25:41 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*m;

	j = 0;
	i = 0;
	m = (char *)big;
	if (!little[j])
		return (m);
	while ((i < len) && m[i])
	{
		j = 0;
		while (m[i + j] == little[j] && (i + j < len))
		{
			j++;
			if (little[j] == '\0')
				return (&m[i]);
		}
		i++;
	}
	return (0);
}
