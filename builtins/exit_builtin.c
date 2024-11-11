/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:11:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/11 17:09:54 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

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
	if (ft_countwords(mini->input, ' ') > 1)
	{
		str = ft_split(mini->input, ' ');
		mini->exit_code = ft_atoi(str[1]);
		if (!str)
		{
			mini->exit_code = 0;
			return (0);
		}
		if (not_number(str[1]))
		{
			exit_anyways(str);
			mini->exit_code = 2;
			return(mini->exit_code);
		}
		else if (str[2])
		{
			mini->running = 1;
			printf("exit: too many arguments\n");
			free_split(str);
			mini->exit_code = 1;
			return (mini->exit_code);
		}
		else
		{
			free_split(str);
			mini->exit_code = mini->exit_code % 256;
			return(mini->exit_code);
		}
	}
	else
	{
		mini->exit_code = 0;
		return(mini->exit_code);
	}
}
