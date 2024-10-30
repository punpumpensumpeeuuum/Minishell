/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/10/29 21:10:09 by jomendes         ###   ########.fr       */
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

int	checkbuiltin(char *str, t_vars *mini)
{
	if (!(ft_strncmp(str, "env", 3)) && !(more(mini->input, 3))) //
	{
		env_builtin(mini);
		return (0);
	}
	else if ((ft_strncmp(str, "pwd", 3) == 0)) //
	{
		pwd_builtin();
		return (0);
	}
	else if ((ft_strncmp(str, "export", 6) == 0)) //
	{
		export_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(str, "cd", 2) == 0)
	{
		cd_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(str, "echo", 4) == 0) //
	{
		echo_builtin(mini);
		return (0);
	}
	else if (ft_strncmp(str, "unset", 5) == 0)
	{
		unset_builtin(mini);
		return (0);
	}
	else if ((ft_strncmp(str, "exit", 4) == 0))
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
	free(a);
	res[j] = NULL;
	return (res);
}

// void	piping(char ***str, t_vars *mini)
// {
// 	int	o;

// 	o = numpipe(mini->input);
// 	if ()
// }

void	fdfd(t_vars *mini)
{
	int i = 0;

	mini->fd = malloc(sizeof(int) * (numpipe(mini->input) + 1) * 2);
	if (!mini->fd)
		return;
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
		dup2(mini->fd[1], 1);
		close(mini->fd[1]);
	}
	else if (i == 2)
	{
		heredoc(mini);
		mini->fd[0] = open("heredoc_tmp.txt", O_RDONLY);
		if (mini->fd[0] == -1)
		{
			ft_printf("%s: No such file or directory\n", str);
			return (-1);
		}
		dup2(mini->fd[0], 0);
		close(mini->fd[0]);
		printf("AQUIEERERERE\n");
	}
	return (0);
}

int	forredirect(char **str, t_vars *mini)
{
	int	j;
	
	j = 0;
	while (str[j])
	{
		if (ft_strncmp(str[j], "<<", 2) == 0)
		{
			if (setinfile(str[j + 1], mini, 2) == 0)
					return (1);
		}
		else if (ft_strncmp(str[j], "<", 1) == 0)
		{
			if (str[j + 1] && access(str[j + 1], R_OK) == 0)
			{
				if (setinfile(str[j + 1], mini, 0) == 0)
					return (1);
				else
				{
					ft_printf("%s: No such file or directory\n", str[j + 1]);
					return (-40);
				}
			}
			else
			{
				ft_printf("%s: No such file or directory\n", str[j + 1]);
				return (-20);
			}
		}
		else
			j++;
	}
	return (0);
}

int	forredirectout(char ***str, t_vars *mini)
{
	int	j;

	j = 0;
	while (str[mini->p][j] && ft_strncmp(str[mini->p][j], ">", 1) != 0)
		j++;
	if (str[mini->p][j] && ft_strncmp(str[mini->p][j], ">", 1) == 0)
	{
		if (str[mini->p][j + 1])
		{
			if (setinfile(str[mini->p][j + 1], mini, 1) == 0)				
				return (1);
			else
				return (-100);
		}
	}
	// if (str[mini->p + 1])
	// {
	// 	piping(str, mini);
	// 	printf("%d\n", mini->p);
	// 	printf("%d\n", mini->fd[mini->p + 1]);
	// 	printf("%d\n", mini->fd[0]);
	// 	printf("%d\n", mini->fd[1]);
	// 	printf("%d\n", mini->fd[2]);
	// 	printf("%d\n", mini->fd[3]);
	// 	printf("%d\n", mini->fd[4]);

	// }
	return (0);
}

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
	s = malloc(sizeof(char *) * j + 1);
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

void	comandddd(char ***str, t_vars *mini)
{
	char	*sim;
	char	**nao;

	mini->pid = fork();
	if (mini->pid == 0)
	{
		if (forredirect(str[mini->p], mini) < 0 || forredirectout(str, mini) < 0)
			exit (3);
		if (checkbuiltin(str[mini->p][mini->i], mini) == 0)
			exit(2);
		sim = ft_strjoin("/", str[mini->p][mini->i]);
		checkpath(sim, mini);
		nao = findflags(str[mini->p], mini->i);
		//printf("mini->check = %s\n", mini->check);
		//printf("nao = %s\n", nao[0]);
		//printf("nao = %s\n", nao[1]);
		if (nao[1] && ft_strncmp(nao[1], "<<", 2) == 0)
		{
			free(nao[1]);
			free(nao[2]);
			nao[1] = ft_strdup("heredoc_tmp.txt");
			nao[2] = NULL;
		}
		if (execve(mini->check, nao, mini->env) == -1)
			ft_printf("%s: command not found\n", str[mini->p][mini->i]);
		free(sim);
		free(nao);
		exit(1);
	}
	else if(mini->pid > 0)
		waitpid(mini->pid, NULL, 0);
	else
		return;
	// VER QUNADO O COMANDO NAO ]E VALIDO
	// VER PIPES
	// ENTREgar
}

int	decide(char **str, t_vars *mini)
{
	mini->i = findbuiltimatrix(str, mini);
	if (mini->i == -2)
		mini->i = findcmdinmatrix(str, mini);
	if (mini->i == -15)
		return (1);
	if (mini->i == -1)
	{
		printf("%s\n", str[0]);
		printf("%s\n", str[1]);
		ft_printf("%s: command not found\n", str[findmistake(str)]);
	}
	return (0);
}

int	checkinput(t_vars *mini)
{
	mini->p = 0;
	char ***tudo = paodelosplit(mini->input, numpipe(mini->input));

	fdfd(mini);
	if (decide(tudo[mini->p], mini) == 0)
	{
		while (mini->p <= numpipe(mini->input) && numpipe(mini->input) >= 0)
		{
			if (mini->check != NULL)
			{
				free(mini->check);
				mini->check = NULL;
			}
			if (tudo[mini->p])
			{
				comandddd(tudo, mini);
				waitpid(mini->pid, NULL, 0);
			}
			mini->p++;
		}	
	}
	free(tudo);	
	free(mini->fd);
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