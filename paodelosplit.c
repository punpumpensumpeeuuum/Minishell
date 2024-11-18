/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paodelosplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:41:20 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/18 17:54:46 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**checksplit(char *str, char delimiter)
{
	char	**split_array;

	split_array = ft_split(str, delimiter);
	if (!split_array)
	{
		free_split(split_array);
		return (NULL);
	}
	return (split_array);
}

char	**allocarrayyyyy(char **a, int j)
{
	int		word_count;
	char	**subarray;

	word_count = ft_countwords(a[j], ' ');
	subarray = malloc(sizeof(char *) * (word_count + 1));
	if (!subarray)
	{
		free_split(a);
		return (NULL);
	}
	return (subarray);
}

int	copycopy(char **b, char **res_subarray, int word_count)
{
	int	i;

	i = 0;
	while (i < word_count)
	{
		res_subarray[i] = ft_strdup(b[i]);
		if (!res_subarray[i])
			return (-1);
		i++;
	}
	res_subarray[i] = NULL;
	return (0);
}

int	splitarray(char ***res, char **a, int pipes)
{
	char	**b;
	int		j;

	j = 0;
	while (j <= pipes)
	{
		b = checksplit(a[j], ' ');
		if (!b)
			return (-1);
		res[j] = allocarrayyyyy(a, j);
		if (!res[j])
		{
			free_split(b);
			return (-1);
		}
		if (copycopy(b, res[j], ft_countwords(a[j], ' ')) == -1)
		{
			free_split(b);
			return (-1);
		}
		free_split(b);
		j++;
	}
	return (0);
}

char	***paodelosplit(char *str, int pipes)
{
	char	***res;
	char	**a;

	res = initpaodelo(pipes);
	if (!res)
		return (NULL);
	a = checksplit(str, '|');
	if (!a)
		return (NULL);
	if (splitarray(res, a, pipes) == -1)
	{
		free_split(a);
		return (NULL);
	}
	free_split(a);
	res[pipes + 1] = NULL;
	return (res);
}
