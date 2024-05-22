/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:51:46 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/09 19:02:42 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)c == (unsigned char)s[i])
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == 0)
		return ((char *)&s[i]);
	return (0);
}
