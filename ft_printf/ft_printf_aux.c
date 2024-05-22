/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:38:42 by dinda-si          #+#    #+#             */
/*   Updated: 2023/11/14 11:10:18 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_newputnbr(long long nb, char c)
{
	if (c == 'd' || c == 'i')
	{
		if (nb < 0)
		{
			ft_putchar_fd('-', 1);
			nb *= -1;
		}
	}
	if (nb > 9)
	{
		ft_newputnbr(nb / 10, c);
		ft_newputnbr(nb % 10, c);
	}
	if (nb < 10)
		ft_putchar_fd(nb + 48, 1);
	return (ft_len_nb(nb, 10));
}

int	ft_hexdecimal(unsigned long long nb, int c)
{
	if (nb > 15)
	{
		ft_hexdecimal(nb / 16, c);
		ft_hexdecimal(nb % 16, c);
	}
	else
	{
		if (nb < 10)
			ft_putchar_fd(nb + 48, 1);
		else
		{
			if (c == 'x')
				ft_putchar_fd(nb - 10 + 'a', 1);
			else
				ft_putchar_fd(nb - 10 + 'A', 1);
		}
	}
	return (ft_len_nb(nb, 16));
}

int	ft_len_nb(unsigned long long nb, int base)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		i++;
		nb = nb / base;
	}
	return (i);
}

int	ft_printadress(unsigned long long adress)
{
	int	i;

	i = 0;
	if (adress < 1)
		i += write(1, "(nil)", 5);
	else
	{
		i += ft_putstr_fd("0x", 1);
		i += ft_hexdecimal(adress, 'x');
	}
	return (i);
}
