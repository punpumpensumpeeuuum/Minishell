/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moreutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:55:42 by elemesmo          #+#    #+#             */
/*   Updated: 2024/11/14 00:00:52 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	truecheckbuilt(char *str)
{
	if (ft_strncmp(str, "cd\0", 3) == 0 || \
		ft_strncmp(str, "unset\0", 6) == 0 || \
		ft_strncmp(str, "exit\0", 5) == 0)
		return (0);
	else if (		ft_strncmp(str, "export\0", 7) == 0 || \
		ft_strncmp(str, "env\0", 4) == 0 || \
		ft_strncmp(str, "pwd\0", 4) == 0 || \
		ft_strncmp(str, "echo\0", 5) == 0)
		return (1);
	else
		return (-2);
}

int	findbuiltimatrix(char **str, t_vars *mini)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "<", 1) != 0 && ft_strncmp(str[i], ">", 1) != 0)
		{
			if (truecheckbuilt(str[i]) == 1)
				return (i);
			else if (truecheckbuilt(str[i]) == 0)
			{
				if (forredirect(str, mini) >= 0 || \
					forredirectout(&str, mini) >= 0)
					checkbuiltin(mini);
				return (-15);
			}
		}
		i++;
	}
	return (-2);
}

int	findcmdinmatrix(char **puzle, t_vars *mini)
{
	int		i;
	char	*str;

	i = 0;
	while (puzle[i])
	{
		str = ft_strjoin("/", puzle[i]);
		if (ft_strncmp(puzle[i], "<", 1) != 0 \
		&& ft_strncmp(puzle[i], ">", 1) != 0)
		{
			checkpath(str, mini);
			if (mini->check != NULL)
			{
				free(str);
				return (i);
			}
		}
		i++;
	}
	free(str);
	return (-1);
}

int	findcmdplace(char *input, t_vars *mini)
{
	int	i;

	i = 0;
	while (input[i])
	{
		checkpath(input, mini);
		i++;
	}
	return (-1);
}
