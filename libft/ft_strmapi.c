/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:02:59 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/10 15:18:15 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*n;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (0);
	n = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!n)
		return (0);
	while (s[i] != '\0')
	{
		n[i] = f(i, s[i]);
		i++;
	}
	n[i] = '\0';
	return (n);
}
