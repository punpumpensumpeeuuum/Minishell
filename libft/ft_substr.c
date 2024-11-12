/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:13:14 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/12 17:32:51 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, int start, int len)
{
	char	*sub;
	int		i;

	i = 0;
	if (!str)
		return (0);
	if (len == 0 || start >= ft_strlen(str))
	{
		sub = malloc(1);
		sub[i] = '\0';
		return (sub);
	}
	if (len <= ft_strlen(str) - start)
		sub = malloc(len + 1);
	else
		sub = malloc(ft_strlen(str) - start + 1);
	if (!sub)
		return (NULL);
	while (str[start] && i < len && start < ft_strlen(str))
		sub[i++] = str[start++];
	sub[i] = '\0';
	return (sub);
}
