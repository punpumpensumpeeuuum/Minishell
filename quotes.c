/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:00:57 by gneto-co          #+#    #+#             */
/*   Updated: 2024/11/14 17:00:57 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *cmd)
{
	int i;
	int single_quote;
	int double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && single_quote == 0)
			single_quote = 1;
		else if (cmd[i] == '\"' && double_quote == 0)
			double_quote = 1;
		else if (cmd[i] == '\'' && single_quote == 1)
			single_quote = 0;
		else if (cmd[i] == '\"' && double_quote == 1)
			double_quote = 0;
		i++;
	}
	if (single_quote != 0 || double_quote != 0)
		return (1);
	return (0);
}

void	remove_single_quote(char *cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != '\'')
		{
			cmd[j] = cmd[i];
			j++;
		}
		i++;
	}
	cmd[j] = '\0';
}

void	remove_double_quote(char *cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] != '"')
		{
			cmd[j] = cmd[i];
			j++;
		}
		i++;
	}
	cmd[j] = '\0';
}

char	*quotescrazy(char *input)
{
	char q;
	int pq;
	int i;
	int nq;

	i = 0;
	nq = 0;
	if (check_quotes(input) == 1)
		return (NULL);
	while (input[i])
	{
		if (ft_strncmp(input, "echo", 4) == 0 || ft_strncmp(input, "export",
				6) == 0)
			return (input);
		if (input[i] == '\'' || input[i] == '"')
		{
			q = input[i];
			pq = i;
			i++;
			nq = 1;
			while (input[i] && input[i] != q)
				i++;
			if (input[i] == q && nq == 1)
			{
				input[i] = ' ';
				input[pq] = ' ';
				nq = 0;
			}
		}
		i++;
	}
	if (nq == 1)
		return (NULL);
	return (input);
}
