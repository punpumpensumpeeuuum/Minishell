/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:30:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/27 23:30:01 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	redirect(t_vars *mini)
{
	int		i;
	int		j;

	i = inputnum(mini->input);
	j = 0;
	i++;
	mini->redrct = malloc(sizeof(char) * \
		(ft_wordlen(&mini->input[i], ' ') + 1));
	while (ft_isalpha(mini->input[i]) == 0)
		i++;
	while (ft_isalpha(mini->input[i]) == 1)
	{
		mini->redrct[j] = mini->input[i];
		i++;
		j++;
	}
	mini->redrct[j] = '\0';
	if (ft_strchr(mini->input, '<'))
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
