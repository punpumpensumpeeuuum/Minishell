/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goodsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:38:14 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/11 18:16:00 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arrangegoodsplit(t_vars *mini)
{
	int	i;
	int	sera;

	i = 0;
	// ft_printf("caralho:%s\n", mini->trueflag[0]);

	while (mini->trueflag[i])
	{
		sera = findcmdplace(mini->trueflag[i], mini);
		if (sera == 0 && i > 0)
		{
			swap_strings(&mini->trueflag[i], &mini->trueflag[i -1]);
			i = 0;
		}
		i++;
	}
	// ft_printf("valor do i:%d\n", i);
	// mini->trueflag = split;
	// mini->trueflag = malloc(sizeof(char *) * i + 1);
	return ;
}

int	countwithout(char *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != '<')
		len++;
	return (len);
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

char	**ft_bettersplit(char *str)
{
	int		i;
	char	**goodflag;
	int		num;
	int		len;

	i = 0;
	if (!str)
		return (0);
	num = countwithout(str);
	goodflag = malloc(sizeof(char *) * (num + 1));
	if (!goodflag)
		return (0);
	goodflag[num] = NULL;
	while (i++ < num)
	{
		while (*str == ' ' && *str && *str == '<')
			str++;
		len = wordllllen(str, ' ');
		goodflag[i] = ft_substr(str, 0, len);
		str += len;
		i++;
	}
	return (goodflag);
}

char	**ft_goodsplit(char	*str)
{
	int		i;
	char	**goodflag;
	int		num;
	int		len;

	i = 0;
	if (!str)
		return (0);
	if (ft_strchr(str, '<') != 0)
		return(ft_bettersplit(str));
	num = checkimportant(str);
	goodflag = malloc(sizeof(char *) * (num + 1));
	if (!goodflag)
		return (0);
	goodflag[num] = NULL;
	while (i++ < num)
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
