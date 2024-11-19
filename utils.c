/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:30:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/19 17:18:22 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getpipepath(char **trueflag, t_vars *mini)
{
	checkpath(ft_strjoin("/", trueflag[0]), mini, 0);
	if (mini->check != NULL)
		return (1);
	return (0);
}

int	wordllllen(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c && s[len] != '<' && s[len] != '>')
		len++;
	return (len);
}

int	inputnum(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_strncmp(&input[i], "<", 1) == 0)
			return (i);
		else if (ft_strncmp(&input[i], ">", 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	numpipe(char *str)
{
	int	numofcmd;
	int	i;

	i = 0;
	numofcmd = 0;
	while (str[i])
	{
		if (str[i] == '|')
			numofcmd++;
		i++;
	}
	return (numofcmd);
}
