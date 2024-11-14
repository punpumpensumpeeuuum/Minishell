/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:11:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/14 20:31:35 by elemesmo         ###   ########.fr       */
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

int	exit_builtin(t_vars *mini)
{
	char	**str;

	printf("exit\n");
	mini->running = 0;
	if (ft_countwords(mini->trueflag[mini->p], ' ') > 1)
	{
		str = ft_split(mini->trueflag[mini->p], ' ');
		g_exit_code = ft_atoi(str[1]);
		if (!str)
		{
			g_exit_code = 0;
			return (0);
		}
		if (not_number(str[1]))
		{
			exit_anyways(str);
			g_exit_code = 2;
			return (g_exit_code);
		}
		else if (str[2])
		{
			mini->running = 1;
			printf("exit: too many arguments\n");
			free_split(str);
			g_exit_code = 1;
			return (g_exit_code);
		}
		else
		{
			free_split(str);
			g_exit_code = g_exit_code % 256;
			return (g_exit_code);
		}
	}
	else
	{
		g_exit_code = 0;
		return (g_exit_code);
	}
}
