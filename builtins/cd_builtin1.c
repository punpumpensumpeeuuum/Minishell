/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:32:05 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/22 12:48:17 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_var(t_vars *mini, char *to_find)
{
	int	i;
	int	to_find_len;

	i = 0;
	to_find_len = ft_strlen(to_find);
	while (i < mini->exp_len)
	{
		if (mini->export[i] && ft_strncmp(mini->export[i], to_find,
				to_find_len) == 0 && mini->export[i][to_find_len] == '=')
			return (i);
		else if (!mini->export[i])
		{
			ft_putstr_fd("Var not find\n", STDERR_FILENO);
			return (-1);
		}
		i++;
	}
	return (-1);
}

char	*ft_getenv(t_vars *mini, char *to_find)
{
	int		index;
	char	*var;

	index = find_var(mini, to_find);
	if (index >= 0)
		var = ft_substr(mini->export[index], ft_strlen(to_find) + 1,
				ft_strlen(mini->export[index]));
	else
		var = ft_strdup("\f");
	return (var);
}

void	get_pwds(t_vars *mini)
{
	int		i;
	char	*buff;
	char	*old_pwd;
	char	cwd[PATH_MAX];

	i = find_var(mini, "PWD");
	if (mini->export[i] && i >= 0)
	{
		buff = mini->export[i];
		mini->export[i] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	}
	i = find_var(mini, "OLDPWD");
	if (mini->export[i] && i >= 0)
	{
		free(mini->export[i]);
		old_pwd = ft_substr(buff, 4, ft_strlen(buff));
		mini->export[i] = ft_strjoin("OLDPWD=", old_pwd);
		free(buff);
		free(old_pwd);
	}
}

void	in_directory(char *directory, t_vars *mini)
{
	if (chdir(directory) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(directory, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		g_exit_code = 1;
	}
	else
		get_pwds(mini);
}
