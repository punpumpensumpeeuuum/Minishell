/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:30:32 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/07 16:45:30 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alreadyprog(t_vars *mini)
{
	char	**prog;

	prog = malloc(sizeof(char *) * 2);
	prog[0] = ft_strdup(&mini->input[2]);
	prog[1] = NULL;
	mini->pid = fork();
	if (mini->pid == 0)
	{
		execve(mini->input, prog, mini->env);
		exit(1);
	}
	return ;
}

int	inputnum(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_strncmp(&input[i], "<", 1) == 0)
			return (i);
		else if (ft_strncmp(&input[i], ">", 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	redirect(t_vars *mini, char *str)
{
	int		i;
	int		j;

	i = inputnum(str);
	if (i == -1)
		return ;
	j = 0;
	i++;
	mini->redrct = malloc(sizeof(char) * \
		(wordllllen(&str[i], ' ') + 1));
	while (ft_isalpha(str[i]) == 0 && str[i])
		i++;
	while (ft_isalpha(str[i]) == 1)
	{
		mini->redrct[j] = str[i];
		i++;
		j++;
	}
	mini->redrct[j] = '\0';
	if (ft_strchr(str, '<'))
		mini->flagfd = 0;
	else
		mini->flagfd = 1;
}

int	numpipe(char *str)
{
	int	numofcmd;
	int	i;

	i = 0;
	numofcmd = 0;
	while (str[i])
	{
		if (str[i] == '|')
			numofcmd++;
		i++;
	}
	return (numofcmd);
}
