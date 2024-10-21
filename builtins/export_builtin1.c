/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 23:46:26 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/19 16:07:21 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     export_check(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
		if (str[0] == '=')
		{
			printf("export: `%c': not a valid identifier\n", str[i]);
    		return (1);
		}
        if ((str[i] >= 'a' && str[i] <= 'z') || 
        (str[i] >= 'A' && str[i] <= 'Z') || (str[i] == '_') ||
		str[i] == '=')
            return (0);
        i++;
    }
	printf("export: `%c': not a valid identifier\n", str[i]);
    return (1);
}

int		str_compare(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s1[i] != '=' && s2[i] && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if ((s1[i] == '=' || !s1[i]) && (s2[i] == '=' || !s2[i]))
         return (0);
	return (1);
}

void    export_var(t_vars *mini)
{
    int     i;
    char    **split;

    i = 1;
    split = ft_split(mini->input, ' ');
	if (!mini->new_export)
		return;
    while (split[i]) 
    {
		mini->exp_len = export_len(mini->export) + 1;
        if (export_check(split[i]) == 0)
        {
			export_update(mini, split[i]);
			i++;
		}
    }
}

void	export_update(t_vars *mini, char *str)
{
	int	i;
    int	done;
    
	i = 0;
    done = 0;
	if (!mini->new_export)
    {
        printf("Error: mini->new_export not initialized.\n");
        return;
	}
	while (i < mini->exp_len)
	{
		if (mini->export[i] && str_compare(mini->export[i], str) == 0)
		{
			free(mini->new_export[i]);
			mini->new_export[i] = ft_strdup(str);
			i++;
			break;
		}
		else if (!mini->export[i] && done == 0)
		{
            done = 1;
            mini->new_export[i] = ft_strdup(str);
			i++;
			continue;
		}
		else if (mini->export[i] && str_compare(mini->export[i], str) != 0)
			mini->new_export[i] = ft_strdup(mini->export[i]);
		i++;
	}
	mini->new_export[i] = NULL;
	export_update1(mini);
}

void	export_update1(t_vars *mini)
{
	int		i;
	char	**temp;
	
	i = 0;
	free_double_array(mini->export, mini);
	temp = realloc(mini->export, sizeof(char *) * (mini->exp_len + 1));
	if (!temp)
		return;
	mini->export = temp;
	while (i < mini->exp_len)
	{
		if (mini->new_export[i])
			mini->export[i] = ft_strdup(mini->new_export[i]);
		else
			mini->export[i] = NULL;
		i++;
    }
	mini->export[i] = NULL;
	sorting_export(mini);
}

void	free_double_array(char **str, t_vars *mini)
{
	int i;

	i = 0;
	while (i < mini->exp_len)
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
}

		void	exp_update(t_vars *mini, char *str)
		{
			int	i;
			char *new_str;

			i = 0;
			new_str = ft_strjoin("/3/4", str);
			if (!new_str)
				return;
			while (mini->export[i] && i < mini->exp_len)
			{
				if (mini->export[i] && 
				ft_strncmp(mini->export[i], str, ft_strlen(str)) == 0)
				{
					free(mini->export[i]);
					mini->export[i] = ft_strdup(new_str);
					free(new_str);
					return;
				}
				i++;
			}
			free(new_str);
			mini->export[i] = NULL;
		}