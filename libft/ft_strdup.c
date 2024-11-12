/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 12:55:55 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/12 17:31:31 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

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
