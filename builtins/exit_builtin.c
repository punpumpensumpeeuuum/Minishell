/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:11:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/27 18:06:51 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	exit_anyways(char **str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_split(str);
}

char	**parse_exit_arguments(t_vars *mini)
{
	char	**str;

	str = ft_split(mini->trueflag[mini->p], ' ');
	if (!str)
	{
		g_exit_code = 0;
		return (NULL);
	}
	g_exit_code = ft_atoi(str[1]);
	return (str);
}

int	handle_exit_conditions(t_vars *mini, char **str)
{
	if (not_number(str[1]))
	{
		exit_anyways(str);
		g_exit_code = 2;
		return (g_exit_code);
	}
	else if (str[2])
	{
		mini->running = 1;
		ft_printf("exit: too many arguments\n");
		free_split(str);
		g_exit_code = 1;
		return (g_exit_code);
	}
	else
	{
		free_split(str);
		g_exit_code %= 256;
		return (g_exit_code);
	}
}

int	exit_builtin(t_vars *mini)
{
	char	**str;

	ft_printf("exit\n");
	mini->running = 0;
	if (ft_countwords(mini->trueflag[mini->p], ' ') > 1)
	{
		str = parse_exit_arguments(mini);
		if (!str)
			return (0);
		return (handle_exit_conditions(mini, str));
	}
	else
	{
		g_exit_code = 0;
		return (g_exit_code);
	}
}
