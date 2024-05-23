/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:30:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/23 18:07:36 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		inputnum(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_strncmp(input[i], "<", 2) == 0)
			return (i);
		else if (ft_strncmp(input[i], ">", 2) == 0)
			return (i);
		i++;
	}
	return (-1);	
}

void	redirect(t_vars *mini)
{
	char	**cmds;
	int		i;

	cmds = ft_split(mini->input, ' ');
	i = inputnum(cmds);
	i++;
	mini->redrct = cmds[i];
	if (ft_strchr(mini->input, '<'))
		mini->flagfd = 0;
	else
		mini->flagfd = 1;
}
