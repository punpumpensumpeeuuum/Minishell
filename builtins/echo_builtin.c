/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:17:33 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/13 17:01:49 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
				printf("%c", '\'');
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

int	echo_builtin(t_vars *mini)
{
	int		i;
	char	**split;
	int		new_line;
	int		in_quotes;

	i = 0;
	new_line = 1;
	in_quotes = 0;
	de_codifiqing(mini->trueflag[mini->p]);
	split = ft_split(mini->trueflag[mini->p], ' ');
	while (ft_strncmp(split[i], "echo", 4) != 0)
		i++;
	if (split[1] == NULL)
	{
		printf("\n");
		free_split(split);
		return (0);
	}
	if (split[i] && ft_strchr(mini->trueflag[mini->p], ' '))
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
			printf("%s", split[i]);
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
				printf("%s", split[i]);
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
			printf("%s", split[i]);
		}
		else if (split[i][0] == '$')
		{
			if (split[i][1] == '?')
				printf("%d", g_exit_code);
			else
				echo_dollar_finish(split[i], 1, mini);
		}
		else if ((split[i][0] == '>' || split[i][0] == '<') && in_quotes == 0)
		{
			i+= 2;
			continue;
		}
		else
			printf("%s", split[i]);
		if (split[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	free_split(split);
	return (0);
}
