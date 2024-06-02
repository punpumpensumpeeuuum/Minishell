/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:30:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/02 22:59:01 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fastcheckpath(t_vars *mini, char **env, int flag, int i)
{
	if (flag == 0)
	{
		mini->flag = ft_split(mini->input, ' ');
		mini->trueflag = ft_goodsplit(mini->input);
		mini->check = checkpath(ft_strjoin("/", mini->trueflag[0]), env);
		if (mini->check != NULL)
			return (1);
		return (0);
	}
	else
	{
		mini->flag = ft_split(mini->input, '|');
		while (mini->flag[i])
		{
			mini->trueflag = ft_goodsplit(mini->flag[i]);
			mini->check = checkpath(ft_strjoin("/", mini->trueflag[0]), env);
			if (mini->check != NULL)
				i++;
			else
				return (0);
		}
		return (1);
	}
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

void	redirect(t_vars *mini, char *str)
{
	int		i;
	int		j;

	i = inputnum(str);
	if (i == -1)
		return ;
	j = 0;
	i++;
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
		mini->flagfd = 0;
	else
		mini->flagfd = 1;
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
