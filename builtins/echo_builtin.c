/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:17:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/11 14:10:11 by jomendes         ###   ########.fr       */
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
			return (1);
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
				ft_printf("%s", &str[j+1]);
            free(env_var);
            break;
		}
		free(env_var);
		i++;
	}
	free(result);
}

void	echo_special(t_vars *mini, char *str)
{
	int		i;
	char	**split;
	int		flag;

	i = 0;
	flag = 0;
	if (str)
	{
		split = ft_split(str, '\'');
		while (str[i])
		{
			if (str[i] == '\'' && flag == 0)
			{
				ft_printf("%c", '\'');
				i++;
			}	
			else if (flag == 0 && (str[i + 1] != '\'' || str[i + 1] != '\0'))
			{
				while (str[i] != '\'')
					i++;
				flag = 1;
			}
			else if (str[i] == '\'' && flag != 0)
			{
				echo_dollar_finish(split[0], 1, mini);
				flag = 0;
			}
			else
				i++;
		}
		free_split(split);
	}
}

int		echo_quote(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] && str[i] == '\'')
				return (1);
			i++;
		}
	}
	return (0);
}

void	de_codifiqing(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			j++;
		if (str[i] == '\a' && j % 2 != 0)
			str[i] = '>';
		else if (str[i] == '\b' && j % 2 != 0)
			str[i] = '<';
		else if (str[i] == '\t' && j % 2 != 0)
			str[i] = '|';
		i++;
	}
}

int	echo_builtin(t_vars *mini)
{
	int		i;
	char	**split;
	int		new_line;
	int		in_quotes;

	i = 0;
	new_line = 1;
	in_quotes = 0;
	de_codifiqing(mini->input);
	split = ft_split(mini->input, ' ');
	while (ft_strncmp(split[i], "echo", 4) != 0)
		i++;
	if (split[1] == NULL)
	{
		ft_printf("\n");
		free_split(split);
		return (0);
	}
	if (split[i] && ft_strchr(mini->input, ' '))
	{
		while (split[++i] && is_flag(split[i]))
			new_line = 0;
	}
	while (split[i])
	{
		
		if (split[i][0] == '\'' && 
		split[i][ft_strlen(split[i]) - 1] == '\'')
		{
			remove_single_quote(split[i]);
			ft_printf("%s", split[i]);
		}	
		else if (split[i][0] == '"' && 
		split[i][ft_strlen(split[i]) - 1] == '"')
		{
			remove_double_quote(split[i]);
			if (echo_quote(split[i]) == 1)
				echo_special(mini, split[i]);
			else if (split[i][0] == '$')
				echo_dollar_finish(split[i], 1, mini);
			else
				ft_printf("%s", split[i]);
		}
		else if (split[i][0] == '"' || split[i][0] == '\'' ||
		split[i][ft_strlen(split[i]) -1] == '"' || 
		split[i][ft_strlen(split[i]) -1] == '\'')
		{
			remove_double_quote(split[i]);
			remove_single_quote(split[i]);
			in_quotes = 1;
			if (split[i][ft_strlen(split[i]) - 1] == '"' ||
			split[i][ft_strlen(split[i]) - 1] == '\'')
			{
				in_quotes = 0;
				continue;
			}
			ft_printf("%s", split[i]);
		}
		else if (split[i][0] == '$')
		{
			if (split[i][1] == '?')
				ft_printf("%d", mini->exit_code);
			else
				echo_dollar_finish(split[i], 1, mini);
		}
		else if ((split[i][0] == '>' || split[i][0] == '<') && in_quotes == 0)
		{
			i+= 2;
			continue;
		}
		else
			ft_printf("%s", split[i]);
		if (split[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	free_split(split);
	return (0);
}
