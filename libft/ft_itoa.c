/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:33:31 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/13 15:01:22 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digit(int n)
{
	int	c;

	c = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		digit;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		digit = ft_digit(n) + 1;
	else
		digit = ft_digit(n);
	s = malloc(sizeof(char) * digit + 1);
	if (!s)
		return (0);
	if (n < 0)
		s[0] = '-';
	if (n < 0)
		n = -n;
	if (n == 0)
		s[0] = '0';
	s[digit] = '\0';
	while (n != 0 && digit >= 0)
	{
		s[digit-- - 1] = n % 10 + '0';
		n /= 10;
	}
	return (s);
}
