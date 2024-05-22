/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:12:52 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/16 16:18:26 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if ((unsigned char)c == (unsigned char)s[i])
			return ((char *)&s[i]);
		i--;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[ft_strlen(s)]);
	return (0);
}
