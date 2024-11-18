/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:42:34 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/18 12:30:02 by jomendes         ###   ########.fr       */
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
		return (0);
	}
	else if (ft_strncmp(mini->trueflag[mini->p], "unset", 5) == 0)
	{
		unset_builtin(mini);
		return (0);
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
			return (0);
		}
		else if ((ft_strncmp(mini->trueflag[mini->p], "pwd", 3) == 0))
		{
			pwd_builtin();
			return (0);
		}
		else if (ft_strncmp(mini->trueflag[mini->p], "echo", 4) == 0)
		{
			echo_builtin(mini);
			return (0);
		}
		else if (checkmorebuiltin(mini) == 0)
			return (1);
		else
			return (1);
	}
	return (1);
}

int	copy_to_input(char **input, int *input_len, \
		int *current_size, const char *str)
{
	int		str_len;
	char	*new_input;

	str_len = ft_strlen(str) + 1;
	while (*input_len + str_len >= *current_size)
	{
		*current_size *= 2;
		new_input = malloc(*current_size);
		if (!new_input)
			return (0);
		ft_strlcpy(new_input, *input, *current_size);
		free(*input);
		*input = new_input;
	}
	ft_strlcat(*input, str, *current_size);
	*input_len += str_len;
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

int	handle_expansion(char **input, int *input_len, int *current_size, const char *str, int *i, t_vars *mini)
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
		free(var);
	}
	if (expanded)
	{
		if (!copy_to_input(input, input_len, current_size, expanded))
			return (free(expanded), 0);
		free(expanded);
	}
	return (1);
}

char	*expand(char *str, t_vars *mini)
{
	int		i;
	int		input_len;
	int		current_size;
	char	*input;

	i = 0;
	input_len = 0;
	current_size = ft_strlen(str) + 1;
	input = malloc(current_size);
	if (!input || find_echo(str) == 0 || find_more(str) == 0)
		return (free(input), str);
	input[0] = '\0';
	while (str[i])
	{
		if (str[i] == '$' && ++i)
		{
			if (!handle_expansion(&input, &input_len, &current_size, str, &i, mini))
				return (free(input), NULL);
		}
		else
		{
			char temp[2] = {str[i++], '\0'};
			if (!copy_to_input(&input, &input_len, &current_size, temp))
				return (free(input), NULL);
		}
	}
	return (free(str), input);
}
