/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/27 22:24:42 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	more(char *input, int i)
{
	while (input[i])
	{
		if (ft_isprint(input[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	checkbuiltin(t_vars *mini)
{
	if (!(ft_strncmp(mini->input, "env", 3)) && !(more(mini->input, 3)))
	{
		env_builtin(mini);
		return (0);
	}
	else if ((ft_strncmp(mini->input, "pwd", 3) == 0))
	{
		pwd_builtin();
		return (0);
	}
	else if ((ft_strncmp(mini->input, "export", 6) == 0))
	{
		export_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(mini->input, "cd", 2) == 0)
	{
		cd_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(mini->input, "echo", 4) == 0)
	{
		echo_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(mini->input, "unset", 5) == 0)
	{
		unset_builtin(mini);
		return (0);
	}
	else if (!(ft_strncmp(mini->input, "exit", 4)))
	{
		exit_builtin(mini);
		return (0);
	}
	else
		return (1);
}

char	***paodelosplit(char *str , int	pipes)
{
	int 	i = 0;
	int		j = 0;
	char	***res = malloc(sizeof(char **) * (pipes + 1));
	char	**a = ft_split(str, '|');
	char	**b;

	while (j <= pipes)
	{		
		b = ft_split(a[j], ' ');
		res[j] = malloc(sizeof(char *) * (ft_countwords(a[j], ' ') + 1));
		while (i < ft_countwords(a[j], ' '))
		{
			res[j][i] = ft_strdup(b[i]);
			i++;
		}
		res[j][i] = NULL;
		j++;
		i = 0;
		free(b);
	}
	res[j] = NULL;
	return (res);
}

void	fdfd(t_vars *mini)
{
	int i = 0;

	while (i < numpipe(mini->input) + 1)
	{
		if (pipe(mini->fd + 2 * i) < 0)
			return ;
		i++;
	}
}

int	setinfile(char *str, t_vars *mini, int i)
{
	if (i == 0)
	{
		mini->fd[0] = open(str, O_RDONLY);
		if (mini->fd[0] == -1)
		{
			ft_printf("%s: No such file or directory\n", str);
			return (-1);
		}
		dup2(mini->fd[0], 0);
		close(mini->fd[0]);
	}
	else if (i == 1)
	{
		mini->fd[1] = open(str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		dup2(mini->fd[1], 0);
		close(mini->fd[1]);
	}
	return (0);
}

int	forredirect(char **str, t_vars *mini)
{
	int	j;
	
	j = 0;
	while (str[j])
	{
		if (ft_strncmp(str[j], "<", 1))
		{
			if (str[j + 1] && access(str[j + 1], R_OK) == 0)
			{
				if (setinfile(str[j + 1], mini, 0) == 0)				
					return (1);
				else
					return (-1);
			}
			else
				return (-1);
		}
		else
			j++;
	}
	return (0);
}

int	forredirectout(char **str, t_vars *mini)
{
	int	j;
	
	j = 0;
	while (str[j])
	{
		if (ft_strncmp(str[j], ">", 1))
		{
			if (str[j + 1] && access(str[j + 1], W_OK) == 0)
			{
				if (setinfile(str[j + 1], mini, 1) == 0)				
					return (1);
				else
					return (-1);
			}
			else
				return (-1);
		}
		else
			j++;
	}
	return (0);
}

void	comandddd(char ***str, t_vars *mini)
{
	int		i;
	char	*sim;

	i = findcmdinmatrix(str[mini->p], mini);
	// if (forredirectout(str[mini->p], mini) == 0)
	// {
	// 	if (str[mini->p + 1])
	// 		// mandar fd para o pipe
	// }
	mini->pid = fork();
	if (mini->pid == 0)
	{
		sim = ft_strjoin("/", str[mini->p][i]);
		if (execve(sim, str[mini->p], mini->env) == -1)
			ft_printf("%s: command not found\n", str[mini->p][i]);
		free(sim);
		exit(1);
	}
	else
		return ;
}

int	checkinput(t_vars *mini)
{
	mini->p = 0;
	mini->i = 0;
	char ***tudo = paodelosplit(mini->input, numpipe(mini->input));

	while (mini->p <= numpipe(mini->input) && numpipe(mini->input) >= 0)
	{
		while (tudo[mini->p][mini->i])
		{
			if (forredirect(tudo[mini->p], mini) == 0 && forredirectout(tudo[mini->p], mini) == 0)
				comandddd(tudo, mini);
			mini->i++;
		}
		mini->p++;
	}	
	waitpid(mini->pid, NULL, 0);
	return (0);
}

// int	checkinput(t_vars *mini)
// {
// 	mini->flagfdin = 0;
// 	mini->flagfdout = 0;
// 	allocfd(numpipe(mini->input), mini);
// 	if (checkbuiltin(mini) == 0)
// 		return (2);
// 	if (check_heredoc(mini) == 0)
// 	{
// 		heredoc(mini);
// 		return (0);
// 	}
// 	if (numpipe(mini->input) > 0)
// 	{
// 		execute(mini, 0, numpipe(mini->input));
// 		return (3);
// 	}
// 	if (fastcheckpath(mini, 0, 0) == 1)
// 	{
// 		execute(mini, 0, numpipe(mini->input));
// 		free(mini->check);
// 		return (4);
// 	}
// 	if (inputnum(mini->input) != -1)
// 	{
// 		printf("mini->input[findcmdplace(mini->input, mini)] = %s\n", &mini->input[findcmdplace(mini->input, mini)]);
// 		checkpath(&mini->input[findcmdplace(mini->input, mini)], mini);
// 		//arrangegoodsplit(mini);
// 		execute(mini, 0, numpipe(mini->input));
// 		free(mini->check);
// 		return (5);
// 	}
// 	ft_printf("%s: command not found\n", mini->flag[0]);
// 	return (0);
// }

int	main(int ac, char **av, char **env)
{
	t_vars	*mini;
	int		exit_value;

	(void)ac;
	(void)av;
	mini = init_mini();
	init_env(env, mini);
	shlvl_update(mini);
	init_export(mini);
	while (mini->running)
	{
		signals_handler();
		mini->input = readline("a espera> ");
		if (!mini->input)
			break;
		if (ft_strlen(mini->input) > 0)
		{
			add_history(mini->input);
			mini->input = quotescrazy(mini->input);
			if (mini->input == NULL)
				printf("Quote error\n");
			else
				printf("%d\n", checkinput(mini));
			free(mini->input);
			free(mini->fd);
		}
	}
	exit_value = mini->exit_code;
	free_env_export(mini);
	return (exit_value);
}
// dois redirects ao memo tempo
// organizar o goodsplit com um swapstrings
// cmds dependetes de input nao cnseguem com pipe
// ver path absoluto aka ./minishell