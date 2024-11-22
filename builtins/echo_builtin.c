/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:17:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/22 17:04:39 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo_dollar_helper(char *result, char *str)
{
	int	j;
	int	u;

	j = 0;
	u = 0;
	while (str[j] == result[u] && str[j] != '=' && result[u] != '\0')
	{
		j++;
		u++;
	}
	if (result[u] == '\0')
		ft_printf("%s", &str[j + 1]);
}

void	echo_dollar_finish(char *str, int k, t_vars *mini, int i)
{
	char	*result;
	char	*env_var;

	result = ft_strdup(str + k);
	if (!result || !str || !mini)
		return ;
	while (i < mini->exp_len && mini->export[i])
	{
		env_var = take_equal(mini->export[i]);
		if (env_var && ft_strncmp(result, env_var, ft_strlen(result)) == 0)
		{
			echo_dollar_helper(result, mini->export[i]);
			free(env_var);
			free(result);
			return ;
		}
		free(env_var);
		i++;
	}
	free(result);
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

void	echo_special(t_vars *mini, char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (str)
		echo_special1(mini, str, &i, &flag);
}

int	echo_builtin(t_vars *mini)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 1;
	if (mini->tudo[mini->p][i] == NULL)
	{
		ft_printf("\n");
		return (0);
	}
	while (mini->tudo[mini->p][i] && is_flag(mini->tudo[mini->p][i]))
	{
		new_line = 0;
		i++;
	}
	i = 1;
	while (mini->tudo[mini->p][i] && ft_strncmp(mini->tudo[mini->p][i], "\f", 1) == 0)
	{
		new_line = 1;
		i++;
	}
	while (mini->tudo[mini->p][i])
	{
		ft_printf("%s", mini->tudo[mini->p][i]);
		if (mini->tudo[mini->p][i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}
