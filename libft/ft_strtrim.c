/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:23:21 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/16 15:37:05 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;

	if (!set)
		return ((char *)s1);
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[end]) && end > 0)
		end--;
	return (ft_substr(s1, 0, (end + 1)));
}
