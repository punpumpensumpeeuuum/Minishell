/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:17:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/17 17:31:11 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (1);
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

int	dollar_flag(char *str)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			n = 1;
		}
		if (n == 0 && str[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

int	dollar_flag_count(char *str)
{
	int i;
	int counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '$')
			counter++;
		i++;
	}
	return (counter);
}

char *take_equal(char *str)
{
	int i;
	char *tmp;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str));
	while (str[i] != '=')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}


void	echo_dollar_finish(char *str, int k, t_vars *mini)
{
	int i;
	char *result;
	int j;
	int u;
	char *env_var;

	j = 0;
	i = 0;
	u = 0;
	result = ft_strdup(str + k);
	if (!str || !mini || !result)
		return ;
	while (i < mini->exp_len && mini->export[i])
	{
		env_var = take_equal(mini->export[i]);
		if (env_var && ft_strncmp(result, env_var, ft_strlen(result)) == 0)
		{
			if (ft_strlen(result) == ft_strlen(env_var))
			{
				str = mini->export[i];
				j = 0;
				i = 0;
			}
			while (str[j] == result[u] && str[j] != '=' && result[u] != '\0')
			{
                j++;
                u++;
            }
            if (result[u] == '\0') 
                printf("%s", &str[j+1]);
            free(env_var);
            break;
		}
		free(env_var);
		i++;
	}
	free(result);
}

int	echo_builtin(t_vars *mini)
{
	int		i;
	char	**split;
	int		new_line;
	char	**last_split;
	int		j;
	
	i = 0;
	j = 0;
	new_line = 1;
	split = ft_split(mini->input, ' ');
	if (split[i] && ft_strchr(mini->input, ' '))
	{
		while (split[i] && is_flag(split[++i]))
			new_line = 0;
	}
	while (split[i] && dollar_flag(split[i]) == 0)
	{
		last_split = ft_split(split[i], '$');
		echo_dollar_finish(split[i], 1, mini);
		if (dollar_flag_count(split[i]) > 1)
		{
			while (last_split[j])
				echo_dollar_finish(last_split[j++], 0, mini);
		}
		if (split[i + 1])
			printf(" ");
		i++;
	}
	while (split[i] && dollar_flag(split[i]) != 0)
	{
		remove_single_quote(split[i]);
		printf("%s", split[i]);
		if (split[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}

