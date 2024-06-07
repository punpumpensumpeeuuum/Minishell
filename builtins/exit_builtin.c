/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:11:29 by jomendes          #+#    #+#             */
/*   Updated: 2024/06/06 23:11:46 by elemesmo         ###   ########.fr       */
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
	// free
	exit(255);
}

int	exit_builtin(t_vars *mini)
{
	char	**str;
	int		exit_status;

	printf("exit\n");
	if (ft_strchr(mini->input, ' '))
	{
		str = ft_split(mini->input, ' ');
		exit_status = ft_atoi(str[1]);
		if (not_number(str[1]))
			exit_anyways(str);
		else if (str[2])
			printf("exit: too many arguments\n");
		else
		{
			free_split(str);
			exit(exit_status);
		}
		free_split(str);
	}
	else
		exit(1);
	return (0);
}
