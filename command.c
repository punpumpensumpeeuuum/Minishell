/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:38:14 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/27 23:16:35 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	wordllllen(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c && s[len] != '<' && s[len] != '>')
		len++;
	return (len);
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

int	checkimportant(char *s)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
			return (n);
		if (s[i] != ' ')
		{
			n++;
			while (s[i] && s[i] != ' ' && s[i] != '<' && s[i] != '>')
				i++;
		}
		else
			i++;
	}
	return (n);
}

char	**ft_goodsplit(char	*str)
{
	int		i;
	char	**goodflag;
	int		num;
	int		len;

	i = 0;
	num = checkimportant(str);
	goodflag = malloc(sizeof(char *) * (num + 1));
	if (!goodflag)
		return (0);
	goodflag[num] = NULL;
	while (i < num)
	{
		while (*str == ' ' && *str)
			str++;
		len = wordllllen(str, ' ');
		goodflag[i] = ft_substr(str, 0, len);
		str += len;
		i++;
	}
	return (goodflag);
}
