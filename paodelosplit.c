/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paodelosplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:41:20 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/28 19:51:35 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**checksplit(char *str, char delimiter)
{
	char	**split_array;
	int		i;

	i = 0;
	while (str[i] && ft_isprint(str[i], 1) == 0)
		return (NULL);
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
	subarray = ft_calloc(sizeof(char *), (word_count + 1));
	if (!subarray)
	{
		free_split(a);
		return (NULL);
	}
	return (subarray);
}

int	copycopy(char **b, char **res_subarray, int word_count, t_vars *mini)
{
	int	i;

	i = 0;
	while (i < word_count)
	{
		b[i] = quotescrazy(b[i], 0, 0, mini);
		if (!b[i])
		{
			ft_printf("Quote error\n");
			return (-2);
		}
		res_subarray[i] = ft_strdup(b[i]);
		if (!res_subarray[i])
			return (-1);
		i++;
	}
	res_subarray[i] = NULL;
	return (0);
}

int	splitarray(char ***res, char **a, int pipes, t_vars *mini)
{
	char	**b;
	int		j;

	j = 0 ;
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
		if (copycopy(b, res[j], ft_countwords(a[j], ' '), mini) < 0)
		{
			free_split(b);
			return (-1);
		}
		free_split(b);
		j++;
	}
	return (0);
}

char	***paodelosplit(char *str, int pipes, t_vars *mini)
{
	char	***res;
	char	**a;

	res = initpaodelo(pipes);
	if (!res)
		return (NULL);
	a = checksplit(str, '|');
	if (!a)
		return (free(res), NULL);
	if (splitarray(res, a, pipes, mini) == -1)
	{
		free_split(a);
		free_res(res);
		return (NULL);
	}
	free_split(a);
	res[pipes + 1] = NULL;
	return (res);
}
