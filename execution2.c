/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:34:43 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/27 15:46:16 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	real_madrid(char *str, t_vars *mini)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && find_flag(str) == 1)
		{
			str[i] = ' ';
			mini->golo = 1;
		}
		i++;
	}
}

void	barcelona(char *str, t_vars *mini)
{
	int	i;

	i = 0;
	while (str[i] && mini->golo == 1)
	{
		if (str[i] == ' ')
			str[i] = '\'';
		i++;
	}
}

int	countflags(char **str, int i)
{
	int	count;
	int	h;

	h = i;
	count = 0;
	while (str[h])
	{
		if ((ft_strncmp(str[h], ">", 1) == 0 || \
			ft_strncmp(str[h], "<", 1) == 0) && \
			str[h + 1] && str[h + 2])
			h += 2;
		else
		{
			count++;
			h++;
		}
	}
	return (count);
}

char	**allocate_flags_array(char **str, int i, int count)
{
	char	**result;
	int		h;
	int		j;

	h = i;
	j = 0;
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (str[h])
	{
		if (ft_strncmp(str[h], ">\0", 2) == 0 || \
			ft_strncmp(str[h], "<\0", 2) == 0 || \
			ft_strncmp(str[h], ">>\0", 3) == 0 || \
			ft_strncmp(str[h], "<<\0", 3) == 0)
			h += 2;
		else
		{
			result[j++] = ft_strdup(str[h]);
			h++;
		}
	}
	result[j] = NULL;
	return (result);
}

char	**findflags(char **str, int i)
{
	int	count;

	count = countflags(str, i);
	return (allocate_flags_array(str, i, count));
}
