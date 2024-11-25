/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:17:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/25 16:28:38 by dinda-si         ###   ########.fr       */
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

void	echo_special(t_vars *mini, char *str)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (str)
		echo_special1(mini, str, &i, &flag);
}

void	check_flaging(t_vars *mini, int *i, int *new_line)
{
	while (mini->tudo[mini->p][*i] && is_flag(mini->tudo[mini->p][*i]))
	{
		*new_line = 0;
		(*i)++;
	}
}

int	echo_builtin(t_vars *mini)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 1;
	de(mini->tudo);
	if (mini->tudo[mini->p][i] == NULL)
		return (ft_printf("\n"), 0);
	check_flaging(mini, &i, &new_line);
	while (mini->tudo[mini->p][i])
	{
		de_codifiqing(mini->tudo[mini->p][i]);
		if (helper(mini, &i, &new_line) == 0)
			return (0);
		if (ft_strncmp(mini->tudo[mini->p][i], ">", 1) == 0
		&& mini->tudo[mini->p][i])
			break ;
		ft_printf("%s", mini->tudo[mini->p][i]);
		if (mini->tudo[mini->p][i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}
