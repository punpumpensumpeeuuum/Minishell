/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:50:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/25 00:20:10 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expanding(char ***tudo, t_vars *mini)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (mini->antiexp == 1)
		return ;
	while (tudo[mini->p][i])
	{
		if (ft_strncmp(tudo[mini->p][i], "<<", 2) == 0)
			return ;
		while (tudo[mini->p][i][j] != '$' && tudo[mini->p][i][j])
			j++;
		if (tudo[mini->p][i][j] == '$' && tudo[mini->p][i][j])
			tudo[mini->p][i] = expand(tudo[mini->p][i], mini, 0);
		i++;
		j = 0;
	}
}

int	handle_expansion_characters(char **input, char *str, int *i, t_vars *mini)
{
	if (!handle_expansion(input, str, i, mini))
	{
		free(*input);
		return (0);
	}
	return (1);
}

int	copy_remaining_characters(char **input, char *str, int *i, t_vars *mini)
{
	char	temp[2];

	temp[0] = str[*i];
	temp[1] = '\0';
	(*i)++;
	if (!copy_to_input(input, mini, temp))
	{
		free(*input);
		return (0);
	}
	return (1);
}

char	*expand(char *str, t_vars *mini, int i)
{
	char	*input;

	real_madrid(str);
	mini->input_len = 0;
	mini->currentsize = ft_strlen(str) + 1;
	input = malloc(mini->currentsize);
	if (!input)
		return (free(input), str);
	input[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$' && ++i)
		{
			if (!handle_expansion_characters(&input, str, &i, mini))
				return (NULL);
		}
		else
		{
			if (!copy_remaining_characters(&input, str, &i, mini))
				return (NULL);
		}
	}
	barcelona(input);
	return (free(str), input);
}
