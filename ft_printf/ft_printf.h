/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:17:49 by dinda-si          #+#    #+#             */
/*   Updated: 2023/11/14 10:58:11 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *str, ...);
int	ft_checkador(va_list va_args, const char *str);
int	ft_hexdecimal(unsigned long long nb, int c);
int	ft_len_nb(unsigned long long nb, int base);
int	ft_newputnbr(long long nb, char c);
int	ft_printadress(unsigned long long adress);

#endif