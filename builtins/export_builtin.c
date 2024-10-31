/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:34:24 by jomendes          #+#    #+#             */
/*   Updated: 2024/10/31 12:59:26 by jomendes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_export(t_vars *mini)
{
    int i = 0;

    mini->export = malloc(sizeof(char *) * (mini->env_len + 1));
    mini->new_export = calloc(mini->env_len + 10, sizeof(char *));
    if (!mini->export || !mini->new_export)
	{
        free(mini->export);
        free(mini->new_export);
        return;
    }
    while (i < mini->env_len)
	{
        if (mini->env[i])
		{
            mini->export[i] = ft_strdup(mini->env[i]);
            if (!mini->export[i])
			{
                while (i > 0)
                    free(mini->export[--i]);
                free(mini->export);
                free(mini->new_export);
                return;
            }
        }
		else
            mini->export[i] = NULL; 
        i++;
    }
    mini->export[i] = NULL;
    mini->exp_len = export_len(mini->export);
}

int		export_redircheck(char *str)
{
	while (str[0])
	{
		if (str[0] == '>' && (str[1] == ' ' || str[1] == '\0'
		|| str[1] == '>'))
			return (0);
	}
	return (1);
}

void	print_export(t_vars *mini)
 {
	int i;

	i = 0;
	mini->exp_len = export_len(mini->export);
	while (i < mini->exp_len)
	{
		if (mini->export[i] && 
		!(ft_strncmp(mini->export[i], "/3/4", 2) == 0))
			printf("declare -x %s\n", mini->export[i]);
		i++;
	}
 }

int	export_builtin(t_vars *mini)
{
	char **split;

	sorting_export(mini);
	split = ft_split(mini->input, ' ');
	if (ft_countwords(mini->input, ' ') > 1)
	{
		
		if (export_redircheck(split[1]) == 0 && split[2])
			print_export(mini);
		else
			export_var(mini);
	}
	else
		print_export(mini);
	free_split(split);
	return (0);
}

void	swap_strings(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		export_len(char **str)
{
	int i;
	int counter;
	
	i = 0;
	counter = 0;
	while (str[i])
	{
		counter++;
		i++;
	}
	return (counter);
}

void	sorting_export(t_vars *mini)
{
	int	i;
	int	swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < mini->exp_len - 1 && 
		mini->export[i] && mini->export[i + 1])
		{
			if (ft_strncmp(mini->export[i], \
				mini->export[i + 1], ft_strlen(mini->export[i])) > 0 && \
				(ft_strncmp(mini->export[i], "/3/4", 2) != 0))
			{
				swap_strings(&mini->export[i], &mini->export[i + 1]);
				swapped = 1;
			}
			i++;
		}
	}
}
