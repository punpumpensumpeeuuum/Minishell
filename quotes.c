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

int	handlequote(char *str, int j)
{
	if (str[j] == '\'')
	{
		str[j] = 5;
		return (5);
	}
	else
	{
		str[j] = 6;
		return (6);
	}
	return (0);
}

void	countformaloc(char *str, int *a, int j)
{
	while (str[j])
	{
		(*a)++;
		if (str[j] == 5 || str[j] == 6)
			(*a)--;
		j++;
	}
}

char	*removedestroy(char *str, int i, int a, int j)
{
	char	*s;

	j = 0;
	countformaloc(str, &a, j);
	s = malloc(sizeof(char) * (a + 1));
	j = 0;
	while (str[j])
	{
		if (str[j] != 5 && str[j] != 6)
		{
			s[i] = str[j];
			i++;
		}
		j++;
	}
	s[i] = '\0';
	free(str);
	return (s);
}

char	*quotescrazy(char *str, int j, int pq)
{
	while (str[j])
	{
		if ((str[j] == '\'' || str[j] == '"') && pq == 0)
			pq = handlequote(str, j);
		if (pq == 5)
		{
			if (str[j] == '\'')
			{
				str[j] = 5;
				pq = 0;
			}
		}
		if (pq == 6)
		{
			if (str[j] == '"')
			{
				str[j] = 6;
				pq = 0;
			}
		}
		j++;
	}
	printf(">>>>>>>>>>> %s\n", str);
	if (pq != 0)
		return (NULL);
	return (removedestroy(str, 0, 0, j));
}

void	preparequotes(t_vars *mini)
{
	int		i;
	char	p;
	int		k;

	i = 0;
	p = '\a';
	k = 0;
	while (mini->input[i])
	{
		if ((mini->input[i] == '\'' || mini->input[i] == '"') && p == '\a')
		{
			k = i;
			p = mini->input[i];
			i++;
		}
		if (p != '\a' && mini->input[i] == 32)
			mini->input[i] = ';';
		if (mini->input[i] == p)
		{
			if (i == k + 1)
			{
				mini->input[i - 1] = ';';
				mini->input[i] = '\0';
			}
			p = '\a';
		}
		i++;
	}
}

void	deprepare(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ';')
			str[i] = 32;
		i++;
	}
}

void	depre(t_vars *mini)
{
	int	i;

	i = 0;
	while (mini->trueflag[i])
	{
		deprepare(mini->trueflag[i]);
		i++;
	}
}

void	de(char ***tudo)
{
	int	p;
	int	i;

	p = 0;
	i = 0;
	while (tudo[p])
	{
		while (tudo[p][i])
		{
			deprepare(tudo[p][i]);
			i++;
		}
		p++;
	}
}
