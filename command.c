/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:38:14 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/24 17:55:34 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkpipe(char *str)
{
	int	numofcmd;
	int	i;
	
	i = 0;
	numofcmd = 1;
	while (str[i])
	{
		if (str[i] == '|')
			numofcmd++;
		i++;
	}
	return (numofcmd);
}

int	checkflag(char *str)
{
	int	nflag;
	int	i;
	
	i = 0;
	nflag = 0;
	while (str[i])
	{
		if (str[i] == '-')
			nflag++;
		i++;
	}
	return (nflag);
}

char	**ft_splitflag(char *str)
{
	int		numflag;
	char	**cmds;
	int		i;
	int		c;

	i = 0;
	c = 0;
	numflag = checkflag(str);
	cmds = malloc(sizeof(char *) * (numflag + 2));
	if (!cmds)
		return (NULL);
	while (*str && *str <= 31 && *str >= 1)
	{
		cmds[c][i] = *str;
		str++;
		i++;
	}
	c++;
	while (*str && *str != '-')
		str++;
	while (*str && *str <= 31 && *str >= 1)
	{
		cmds[c][i] = *str;
		str++;
		i++;
	}
	return (cmds);
}
