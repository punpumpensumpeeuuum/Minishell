/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:50:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/22 15:33:53 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expanding(char ***tudo, t_vars *mini)
{
	int	i;

	i = 0;
	while (tudo[mini->p][i])
	{
		if (ft_strncmp(tudo[mini->p][i], "<<", 2) == 0)
			return ;
		if (tudo[mini->p][i][0] == '$')
			tudo[mini->p][i] = expand(tudo[mini->p][i], mini);
		i++;
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

char	*expand(char *str, t_vars *mini)
{
	int		i;
	char	*input;

	i = 0;
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
	return (free(str), input);
}
