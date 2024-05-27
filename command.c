/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:38:14 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/27 18:48:52 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	findredirect(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (i);
		i++;
	}
	return (0);
}



int	findcmdplace(char *str, char **env)
{
	int		i;
	char	*cmdt;
	char	*check;	

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
		{
			cmdt = ft_strjoin("/", &str[i - 1]);
			check = checkpath(cmdt, env);
			if (check != NULL)
				return (1);
		}
		i++;
	}
	return (0);
}

int	checkimportant(char *str, char **env)
{
	int	flagnum;
	int	i;

	i = 0;
	flagnum = 0;
	while (str[i])
	{
		if (str[i] == '-' && ft_isalpha(str[i + 1]) == 1)
			flagnum++;
		i++;
	}
	if (findcmdplace(str, env) == 1)
		flagnum++;
	return (flagnum + 1);
}

char	**ft_goodsplit(char	*str, char **env)
{
	int		i;
	char	**goodflag;
	int		num;
	int		cmdplace;
	int		len;

	i = 0;
	num = checkimportant(str, env);
	goodflag = malloc(sizeof(char *) * (num + 1));
	if (!goodflag)
		return (0);
	cmdplace = findcmdplace(str, env);
	while (i < num && (*str != '<' || *str != '>'))
	{
		if (cmdplace > 0)
		{	
			goodflag[i] = ft_substr(str, cmdplace - 1, ft_wordlen(str, ' '));
			cmdplace = -1;
			i++;
		}
		len = ft_wordlen(str, ' ');
		goodflag[i] = ft_substr(str, 0, len);
		str += len;		
		i++;
	}
	goodflag[num] = NULL;
	return (goodflag);
}
