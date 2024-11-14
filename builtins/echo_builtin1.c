/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:23:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/14 16:07:09 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (1);
	while (str[i])
	{
		if (str[i] == '-')
		{
			i++;
			if (str[i] == 'n')
			{
				while (str[i] == 'n')
					i++;
				if (str[i] != '\0')
					return (0);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

int	dollar_flag(char *str)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			n = 1;
			return (1);
		}
		if (n == 0 && str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

int	dollar_flag_count(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '$')
			counter++;
		i++;
	}
	return (counter);
}

char	*take_equal(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	echo_quote(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] && str[i] == '\'')
				return (1);
			i++;
		}
	}
	return (0);
}
