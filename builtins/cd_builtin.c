/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:45:25 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/12 12:26:42 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		find_var(t_vars *mini, char *to_find)
{
	int i;
	int to_find_len;

	i = 0;
	to_find_len = ft_strlen(to_find);
	while (i < mini->exp_len)
	{
		if (mini->export[i] && ft_strncmp(mini->export[i], to_find, to_find_len) == 0
		&& mini->export[i][to_find_len] == '=')
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

void	get_pwds(t_vars *mini)
{
	int i;
	char *buff;
	char *old_pwd;
	char cwd[PATH_MAX];
	
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
		mini->exit_code = 1;
	}
	else
		get_pwds(mini);
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

char	*ft_getenv(t_vars *mini ,char	*to_find)
{
	int	index;
	char *var;

	index = find_var(mini, to_find);
	if (index >= 0)
		var = ft_substr(mini->export[index], ft_strlen(to_find) + 1, \
		ft_strlen(mini->export[index]));
	else
		var = NULL;
	return (var);
}

int		cd_special_1(t_vars *mini)
{
	char	**split;
	split = ft_split(mini->input, ' ');
	if (ft_countwords(mini->input, ' ') == 2)
	{
		if (split[1] && ft_strncmp(split[1], "~", 1) == 0)
		{
			free_split(split);
			return (0);
		}
	}
	free_split(split);
	return (-1);
}

void	cd_1_arg(t_vars *mini)
{
	char *directory;
	
	directory = ft_getenv(mini, "HOME");
	if (!directory)
	{
		ft_putstr_fd("minishel: cd: HOME not set", STDERR_FILENO);
		return;
	}
	if (directory)
		in_directory(directory, mini);
	free(directory);
}

void	cd_2_args(t_vars *mini)
{
	char	**split;
	char	*directory;
	
	directory = NULL;
	split = ft_split(mini->input, ' ');
	if (split[1] && ft_strncmp(split[1], "-", 1) == 0)
	{
		directory = ft_getenv(mini, "OLDPWD");
		if (!directory)
		{
			ft_putstr_fd("minishel: cd: OLDPWD not set", STDERR_FILENO);
			free_split(split);
			return;
		}
	}
	else
		directory = ft_strdup(split[1]);
	if (directory)
	{
		in_directory(directory, mini);
		free(directory);
		free_split(split);
	}
}

void	cd_builtin(t_vars *mini)
{
	int i;

	i = ft_countwords(mini->input, ' ');
	if (i == 1 || cd_special_1(mini) == 0)
		cd_1_arg(mini);
	else if (i == 2)
		cd_2_args(mini);
	else
	{
		ft_putendl_fd("minishell: cd: Too many arguments", STDERR_FILENO);
		return;
	}
}