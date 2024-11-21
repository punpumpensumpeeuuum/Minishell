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

// int	check_quotes(char *cmd)
// {
// 	int	i;
// 	int	single_quote;
// 	int	double_quote;

// 	i = 0;
// 	single_quote = 0;
// 	double_quote = 0;
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '\'' && single_quote == 0)
// 			single_quote = 1;
// 		else if (cmd[i] == '\"' && double_quote == 0)
// 			double_quote = 1;
// 		else if (cmd[i] == '\'' && single_quote == 1)
// 			single_quote = 0;
// 		else if (cmd[i] == '\"' && double_quote == 1)
// 			double_quote = 0;
// 		i++;
// 	}
// 	if (single_quote != 0 || double_quote != 0)
// 		return (1);
// 	return (0);
// }

// void	remove_single_quote(char *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (cmd[i] != '\0')
// 	{
// 		if (cmd[i] != '\'')
// 		{
// 			cmd[j] = cmd[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	cmd[j] = '\0';
// }

// void	remove_double_quote(char *cmd)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (cmd[i] != '\0')
// 	{
// 		if (cmd[i] != '"')
// 		{
// 			cmd[j] = cmd[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	cmd[j] = '\0';
// }

// void	crazy(t_vars *mini)
// {
// 	if (mini->input[mini->j] == '\'' || mini->input[mini->j] == '"')
// 	{
// 		mini->q = mini->input[mini->j];
// 		mini->pq = mini->j;
// 		mini->j++;
// 		mini->nq = 1;
// 		while (mini->input[mini->j] && mini->input[mini->j] != mini->q)
// 			mini->j++;
// 		if (mini->input[mini->j] == mini->q && mini->nq == 1)
// 		{
// 			mini->input[mini->j] = ' ';
// 			mini->input[mini->pq] = ' ';
// 			mini->nq = 0;
// 		}
// 	}
// 	mini->j++;
// }

// char	*quotescrazy(t_vars *mini)
// {
// 	mini->j = 0;
// 	mini->nq = 0;
// 	if (check_quotes(mini->input) == 1)
// 		return (NULL);
// 	while (mini->input[mini->j])
// 	{
// 		if (ft_strncmp(mini->input, "echo", 4) == 0
// 			|| ft_strncmp(mini->input, "export", 6) == 0)
// 			return (mini->input);
// 		crazy(mini);
// 	}
// 	if (mini->nq == 1)
// 		return (NULL);
// 	return (mini->input);
// }

int	handlequote(t_vars *mini)
{
	if (mini->input[mini->j] == '\'')
	{
		mini->input[mini->j] = 5;
		return (5);
	}
	else
	{
		mini->input[mini->j] = 6;
		return (6);
	}
	return (0);
}

void	countformaloc(t_vars *mini, int *a)
{
	while (mini->input[mini->j])
	{
		(*a)++;
		if (mini->input[mini->j] == 5 || mini->input[mini->j] == 6)
			(*a)--;
		mini->j++;
	}
}

char	*removedestroy(t_vars *mini, int i, int a)
{
	char	*s;

	mini->j = 0;
	countformaloc(mini, &a);
	s = malloc(sizeof(char) * (a + 1));
	mini->j = 0;
	while (mini->input[mini->j])
	{
		if (mini->input[mini->j] != 5 && mini->input[mini->j] != 6)
		{
			s[i] = mini->input[mini->j];
			i++;
		}
		mini->j++;
	}
	s[i] = '\0';
	free(mini->input);
	return (s);
}

char	*quotescrazy(t_vars *mini)
{
	mini->j = 0;
	mini->pq = 0;
	while (mini->input[mini->j])
	{
		if ((mini->input[mini->j] == '\'' || mini->input[mini->j] == '"') && mini->pq == 0)
			mini->pq = handlequote(mini);
		if (mini->pq == 5)
		{
			if (mini->input[mini->j] == '\'')
			{
				mini->input[mini->j] = 5;	
				mini->pq = 0;			
			}
		}
		if (mini->pq == 6)
		{
			if (mini->input[mini->j] == '"')
			{
				mini->input[mini->j] = 6;	
				mini->pq = 0;			
			}
		}
		mini->j++;
	}
	return (removedestroy(mini, 0, 0));
}
