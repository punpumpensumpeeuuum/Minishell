/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:55:55 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/12 22:51:37 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;

	if (!s)
		return (NULL);
	dest = malloc((ft_strlen(s) + 1));
	i = 0;
	if (!dest)
		return (NULL);
	while (i <= (ft_strlen(s)))
	{
		dest[i] = s[i];
		i++;
	}
	return (dest);
}
