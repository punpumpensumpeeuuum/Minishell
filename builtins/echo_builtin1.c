/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:23:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/25 15:34:12 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (1);
	while (str[i])
	{
		if (str[i] == '-')
		{
			i++;
			if (str[i] == 'n')
			{
				while (str[i] == 'n')
					i++;
				if (str[i] != '\0')
					return (0);
			}
			else
				return (0);
		}
		else
			return (0);
	}
	return (1);
}

int	dollar_flag_count(char *str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '$')
			counter++;
		i++;
	}
	return (counter);
}

char	*take_equal(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

void	echo_special1(t_vars *mini, char *str, int *i, int *flag)
{
	char	**split;

	split = ft_split(str, '\'');
	while (str[*i])
	{
		if (str[*i] == '\'' && *flag == 0)
		{
			ft_printf("%c", '\'');
			(*i)++;
		}
		else if (*flag == 0 && (str[*i + 1] != '\'' || str[*i + 1] != '\0'))
		{
			while (str[*i] != '\'')
				(*i)++;
			*flag = 1;
		}
		else if (str[*i] == '\'' && *flag != 0)
		{
			echo_dollar_finish(split[0], 1, mini, 0);
			*flag = 0;
		}
		else
			(*i)++;
	}
	free_split(split);
}

int	helper(t_vars *mini, int *i, int *new_line)
{
	if ((ft_strncmp(mini->tudo[mini->p][*i], ">\0", 2) == 0 || \
		ft_strncmp(mini->tudo[mini->p][*i], ">>\0", 3) == 0) && \
		mini->tudo[mini->p][*i + 2] && mini->tudo[mini->p][*i + 1])
	{
		*i += 2;
		if (!mini->tudo[mini->p][*i])
		{
			*new_line = 1;
			return (0);
		}
	}
	return (1);
}
