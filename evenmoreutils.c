/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evenmoreutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:13:36 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/28 11:30:19 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkprint(char *str)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (ft_isprint(str[i]) == 1)
			a++;
		i++;
	}
	if (a < 1)
		return (2);
	return (0);
}

char	*trimtrimtrim(char *str, int i)
{
	i = 0;
	while (str[i] && strncmp(&str[i], "./", 2) != 0)
		i++;
	if (strncmp(&str[i], "./", 2) == 0)
		return (str);
	return (str);
}

int	findmistake(char **str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (-1);
	if (str[i][0] == '<')
	{
		if (str[2])
			return (2);
		else
			return (-1);
	}
	else
		return (0);
}

int	more(char *input, int i)
{
	while (input[i])
	{
		if (ft_isprint(input[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
