/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moreutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:55:42 by elemesmo          #+#    #+#             */
/*   Updated: 2024/06/12 17:47:19 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trimtrimtrim(char *str)
{
	// try to remove everthing execpt the ./minishell caralho
}

int	findcmdinmatrix(char **puzle, t_vars *mini)
{
	int	i;
	int	ver;

	i = 0;
	while (puzle[i])
	{
		ver = findcmdplace(puzle[i], mini);
		if (ver >= 0)
			return (i);
		i++;
	}
	return (0);
}

int	findcmdplace(char *input, t_vars *mini)
{
	char	*word;
	char	*path;
	int		start;
	int		end;

	start = 0;
	while (input[start])
	{
		while (input[start] && !ft_isprint(input[start]))
			start++;
		if (!input[start])
			break ;
		end = start;
		while (input[end] && ft_isprint(input[end]))
			end++;
		word = strndup(input + start, end - start);
		path = ft_strjoin("/", word);
		free(word);
		checkpath(path, mini);
		free(path);
		if (mini->check != NULL)
			return (start);
		start = end;
	}
	return (-1);
}
