/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:26:21 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/28 19:01:14 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

void	codifiqing_export(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			j++;
		if (str[i] == '>' && j % 2 != 0)
			str[i] = '\a';
		else if (str[i] == '<' && j % 2 != 0)
			str[i] = '\b';
		else if (str[i] == '|' && j % 2 != 0)
			str[i] = '\t';
		else if (str[i] == ' ' && j % 2 != 0)
			str[i] = '\f';
		i++;
	}
}

void	de_codifiqing_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\f')
			str[i] = ' ';
		i++;
	}
}

int	find_flag(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	free_res(char ***res)
{
	int	i;

	i = 0;
	if (!res)
		return ;
	while (res[i])
	{
		free_split(res[i]);
		i++;
	}
	free(res);
}
