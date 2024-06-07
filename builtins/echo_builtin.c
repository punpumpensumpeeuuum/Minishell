/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:17:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/06/07 12:07:08 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 0;
	// printf("str = %s\n", str);
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

int	
echo_builtin(t_vars *mini)
{
	int		i;
	char	**split;
	int		new_line;
	// int u = -1;

	i = 0;
	new_line = 1;
	split = ft_split(mini->input, ' ');
	// while (split[++u] != NULL)
	// 	printf("mini->input[u] = %s\n", split[u]);
	if (ft_strchr(mini->input, ' '))
	{
		while (split && is_flag(split[++i]))
			new_line = 0;
	}
	while (split[i])
	{
		printf("%s", split[i]);
		if (split[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
