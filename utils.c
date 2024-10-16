/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:30:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/16 18:52:30 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getpipepath(char **trueflag, t_vars *mini)
{
	checkpath(ft_strjoin("/", trueflag[0]), mini);
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
		else if (ft_strncmp(&input[i], ">>", 1) == 0)
			return (-3);
		i++;
	}
	return (-1);
}

void	redirect(t_vars *mini, char *str)
{
	int		i;
	int		j;

	i = inputnum(str);
	if (i == -1)
		return ;
	j = 0;
	i++;
	printf("str = %s", str);
	mini->redrct = malloc(sizeof(char) * \
		(wordllllen(&str[i], ' ') + 1));
	while (ft_isalpha(str[i]) == 0 && str[i])
		i++;
	while (ft_isalpha(str[i]) == 1)
	{
		mini->redrct[j] = str[i];
		i++;
		j++;
	}
	mini->redrct[j] = '\0';
	if (ft_strchr(str, '<'))
		mini->flagfdin = 1;
	else if (ft_strchr(str, '>'))
		mini->flagfdout = 1;
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
