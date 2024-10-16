/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:11:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/07/01 12:26:43 by jomendes         ###   ########.fr       */
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
	printf("exit %s: numeric argument required\n", str[1]);
	free_split(str);
	exit(2);
}

int	exit_builtin(t_vars *mini)
{
	char	**str;
	int		exit_status;

	printf("exit\n");
	if (ft_strchr(mini->input, ' '))
	{
		str = ft_split(mini->input, ' ');
		if (not_number(str[1]))
			exit_anyways(str);
		else if (str[2])
		{
			printf("exit: too many arguments\n");
			free_split(str);
			return (1);
		}
		else
		{
			exit_status = ft_atoi(str[1]);
			free_split(str);
			exit(exit_status);
		}
	}
	else
		exit(1);
	return (0);
}
