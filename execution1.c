/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:42:34 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/25 17:13:59 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkmorebuiltin(t_vars *mini)
{
	if (ft_strncmp(mini->trueflag[mini->p], "cd", 2) == 0)
	{
		cd_builtin(mini);
		return (0);
	}
	else if ((ft_strncmp(mini->trueflag[mini->p], "export", 6) == 0))
	{
		export_builtin(mini);
		return (g_exit_code = 0, 0);
	}
	else if (ft_strncmp(mini->trueflag[mini->p], "unset", 5) == 0)
	{
		unset_builtin(mini);
		return (g_exit_code = 0, 0);
	}
	else if (ft_strncmp(mini->trueflag[mini->p], "exit", 4) == 0)
	{
		exit_builtin(mini);
		return (0);
	}
	return (1);
}

int	checkbuiltin(t_vars *mini)
{
	while (mini->trueflag[mini->p])
	{
		if (!(ft_strncmp(mini->trueflag[mini->p], "env", 3))
			&& !(more(mini->input, 3)))
		{
			env_builtin(mini);
			return (g_exit_code = 0, 0);
		}
		else if ((ft_strncmp(mini->trueflag[mini->p], "pwd", 3) == 0))
		{
			pwd_builtin();
			return (g_exit_code = 0, 0);
		}
		else if (ft_strncmp(mini->trueflag[mini->p], "echo", 4) == 0)
		{
			echo_builtin(mini);
			return (g_exit_code = 0, 0);
		}
		else if (checkmorebuiltin(mini) == 0)
			return (1);
		else
			return (1);
	}
	return (1);
}

int	copy_to_input(char **input, t_vars *mini, \
		const char *str)
{
	int		str_len;
	char	*new_input;

	str_len = ft_strlen(str) + 1;
	while (mini->input_len + str_len >= mini->currentsize)
	{
		mini->currentsize *= 2;
		new_input = malloc(mini->currentsize);
		if (!new_input)
			return (0);
		ft_strlcpy(new_input, *input, mini->currentsize);
		free(*input);
		*input = new_input;
	}
	ft_strlcat(*input, str, mini->currentsize);
	mini->input_len += str_len;
	return (1);
}

char	*extract_var_name(const char *str, int *i)
{
	int		start;
	int		length;
	char	*var;

	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '$')
		(*i)++;
	length = *i - start;
	var = malloc(length + 1);
	if (!var)
		return (NULL);
	ft_strlcpy(var, &str[start], length + 1);
	return (var);
}

int	handle_expansion(char **input, const char *str, int *i, t_vars *mini)
{
	char	*expanded;
	char	*var;

	if (str[*i] == '?')
	{
		expanded = convert_exit_code();
		(*i)++;
	}
	else
	{
		var = extract_var_name(str, i);
		if (!var)
			return (0);
		expanded = ft_getenv(mini, var);
		if (!expanded)
		{
			free(var);
			var = NULL;
			return (1);
		}
		free(var);
		var = NULL;
	}
	handle_expansion_helper(expanded, input, mini);
	return (1);
}
