/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:21:11 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/20 11:25:15 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	if (s > d)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char d[] = {'m','a','l','u','q','u','i','c','e'};
	char s[] = {'b','a','t','a','t','a'};

	printf("%s\n", (char *)ft_memmove(&d,&s,3));
}*/
