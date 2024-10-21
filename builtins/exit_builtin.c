/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:11:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/18 13:11:26 by jomendes         ###   ########.fr       */
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
	int		exit_status;

	printf("exit\n");
	exit_status = 0;
	if (ft_strchr(mini->input, ' '))
	{
		str = ft_split(mini->input, ' ');
		if (!str)
		{
			//free_env_export(mini);
			return (1);
		}
		exit_status = ft_atoi(str[1]);
		if (not_number(str[1]))
		{
			exit_anyways(str);
			//free_env_export(mini);
			exit(2);
		}
		else if (str[2])
		{
			printf("exit: too many arguments\n");
			free_split(str);
			//free_env_export(mini);
			return (1);
		}
		else
		{
			free_split(str);
			//free_env_export(mini);
			exit(exit_status % 256);
		}
	}
	else
	{
		free_env_export(mini);
		exit(1);
	}	
	return (0);
}
