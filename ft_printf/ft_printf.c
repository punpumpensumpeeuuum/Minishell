/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:20:55 by dinda-si          #+#    #+#             */
/*   Updated: 2023/11/14 10:57:54 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_checkador(va_list va_args, const char *str)
{
	int			returnval;
	long long	nb;

	returnval = 0;
	if (*str == 'c')
		returnval += ft_putchar_fd(va_arg(va_args, int), 1);
	else if (*str == 's')
		returnval += ft_putstr_fd(va_arg(va_args, char *), 1);
	else if (*str == 'p')
		returnval += ft_printadress(va_arg(va_args, unsigned long long));
	else if (*str == 'd' || *str == 'i')
	{
		nb = va_arg(va_args, int);
		if (nb < 0)
			returnval = 1;
		returnval += ft_newputnbr(nb, *str);
	}
	else if (*str == 'u')
		returnval += ft_newputnbr(va_arg(va_args, unsigned int), *str);
	else if (*str == 'x' || *str == 'X')
		returnval += ft_hexdecimal(va_arg(va_args, unsigned int), *str);
	else if (*str == '%')
		returnval += ft_putchar_fd('%', 1);
	return (returnval);
}

int	ft_printf(const char *str, ...)
{
	va_list	va_args;
	int		returnval;

	returnval = 0;
	va_start(va_args, str);
	while (*str != 0)
	{
		if (*str == '%')
		{
			str++;
			returnval += ft_checkador(va_args, str);
			str++;
		}
		else
		{
			ft_putchar_fd(*str++, 1);
			returnval++;
		}
	}
	return (returnval);
}
