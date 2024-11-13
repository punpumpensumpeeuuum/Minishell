/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 08:42:34 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/13 09:30:05 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**findflags(char **str, int i)
{
	char	**s;
	int		h;
	int		j;
	int		l;

	h = 0;
	j = 0;
	while (str[h])
	{
		if (ft_strncmp(str[h], "<", 1) != 0)
			j++;
		if (ft_strncmp(str[h], ">", 1) == 0)
			break;
		h++;
	}
	l = 0;
	s = malloc(sizeof(char *) * (j + 1));
	if (!s)
		return (NULL);
	s[l] = ft_strdup(str[i]);
	l++;
	j = i + 1;
	while (j < h)
	{
		s[l] = ft_strdup(str[j]);	
		l++;
		j++;
	}
	if (l < h)
	{
		s[l] = ft_strdup(str[i - 1]);
		l++;
	}
	s[l] = NULL;
	return (s);
}

int	checkbuiltin(t_vars *mini)
{
	while (mini->trueflag[mini->p])
	{
		if (!(ft_strncmp(mini->trueflag[mini->p], "env", 3)) && !(more(mini->input, 3))) //
		{
			env_builtin(mini);
			return (0);
		}
		else if ((ft_strncmp(mini->trueflag[mini->p], " pwd", 3) == 0)) //
		{
			pwd_builtin();
			return (0);
		}
		else if ((ft_strncmp(mini->trueflag[mini->p], "export", 6) == 0))
		{
			export_builtin(mini);
			return (0);
		}
		else if (ft_strncmp(mini->trueflag[mini->p], "echo", 4) == 0) //
		{
			echo_builtin(mini);
			return (0);
		}
		else if (ft_strncmp(mini->trueflag[mini->p], "cd", 2) == 0)
		{
			cd_builtin(mini);
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
		else
			return (1);
	}
	return (1);
}

char *expand(char *str, t_vars *mini)
{
    int 	i;
    int 	j;
	int		start;
	int		length;
	int		len;
    char	*var;
	char	*expanded;
	char	*input;
	int		input_len;

	i = 0;
	if (find_echo(str) == 0)
		return (str);
	input_len = ft_strlen(str + 1);
	input = malloc(sizeof(char *) * input_len + 1);
	if (!input)
		return (NULL);
	input[0] = '\0';
    while (str[i])
    {
        if (str[i] == '$')
        {
            i++;
			if (str[i] == '?')
			{
				
				expanded = convert_exit_code(mini);
				i++;
            }
            else
			{
				start = i;
           		while (str[i] && str[i] != ' ' && str[i] != '$' &&
				str[i] != '\0')
                	i++;
            	length = i - start;
            	var = (char *)malloc((length + 1) * sizeof(char));
            	if (!var)
				{
					free(input);
					return (NULL);
				}
				j = 0;
        		while (j < length)
				{
					var[j] = str[start + j];
					j++;
				}
				var[j] = '\0';
				expanded = ft_getenv(mini, var);
				free(var);
			}
			if (expanded)
			{
				input_len += strlen(expanded);
				input = realloc(input, input_len);
				if (!input)
				{
					free(input);
					return NULL;
				}
				ft_strlcat(input, expanded, input_len);
				free(expanded);
			}
		}
		else
		{
			len = strlen(input);
			input_len += 1;
			input = realloc(input, input_len);
			if (!input)
			{
				free(input);
				return NULL;
			}
			input[len] = str[i];
			input[len + 1] = '\0';
			i++;
		}
	}
	return (input);
}