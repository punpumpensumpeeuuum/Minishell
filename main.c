/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:21:17 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/11 20:08:33 by dinda-si         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (mini->trueflag[i])
	{
		if (!(ft_strncmp(mini->trueflag[i], "env\0", 4)) && !(more(mini->input, 3))) //
		{
			env_builtin(mini);
			return (0);
		}
		else if ((ft_strncmp(mini->trueflag[i], "pwd\0", 4) == 0)) //
		{
			pwd_builtin();
			return (0);
		}
		else if ((ft_strncmp(mini->trueflag[i], "export\0", 7) == 0))
		{
			export_builtin(mini);
			return (0);
		}
		else if (ft_strncmp(mini->trueflag[i], "echo\0", 5) == 0) //
		{
			echo_builtin(mini);
			return (0);
		}
		else if (ft_strncmp(mini->trueflag[i], "cd\0", 3) == 0)
		{
			cd_builtin(mini);
			return (0);
		}
		else if (ft_strncmp(mini->trueflag[i], "unset\0", 6) == 0)
		{
			unset_builtin(mini);
			return (0);
		}
		else if (ft_strncmp(mini->trueflag[i], "exit\0", 5) == 0)
		{	
			exit_builtin(mini);
			return (0);
		}
		i++;
	}
	return (1);
}

char	***paodelosplit(char *str , int	pipes)
{
	int 	i = 0;
	int		j = 0;
	char	***res = malloc(sizeof(char **) * (pipes + 2));
	char	**a = ft_split(str, '|');
	char	**b;

	if (!a)
	{
		free_split(a);
		return (NULL);
	}
	while (j <= pipes)
	{	
		b = ft_split(a[j], ' ');
		if (!b)
		{
			free_split(b);
			return (NULL);
		}
		res[j] = malloc(sizeof(char *) * (ft_countwords(a[j], ' ') + 1));
		if(!res[j])
		{
			free_split(a);
			free_split(b);
			free(res);
			return (NULL);	
		}
		while (i < ft_countwords(a[j], ' '))
		{
			res[j][i] = ft_strdup(b[i]);
			i++;
		}
		res[j][i] = NULL;
		j++;
		i = 0;
		free_split(b);
	}
	free_split(a);
	res[j] = NULL;
	return (res);
}

void	fdfd(t_vars *mini)
{
	int i = 0;

	mini->fd = malloc(sizeof(int) * (numpipe(mini->input) + 1) * 2);
	if (!mini->fd)
		return;
	while (i < numpipe(mini->input) + 1)
	{
		if (pipe(mini->fd + 2 * i) < 0)
		{
			// perror("Failed to create pipe");
			// free(mini->fd);
			return ;
		}
		i++;
	}
}

void	piping(char ***str, t_vars *mini, int ta)
{
	int	o;

	o = numpipe(mini->input);
	if (mini->p == 0 && str[mini->p + 1])
	{
		if (ta == 1)
			return;
		// printf("%d\n", mini->fd[mini->p + 1]);
		dup2(mini->fd[mini->p + 1], 1);
		closeall(mini);
	}
	else if (mini->p > 0 && mini->p < o && str[mini->p + 1]) 
	{
		if (ta == 1)
			return;
		// printf("%d\n", mini->fd[2 * (mini->p - 1)]);
		// printf("%d\n", mini->fd[2 * mini->p + 1]);
		dup2(mini->fd[2 * (mini->p - 1)], 0);
		dup2(mini->fd[2 * mini->p + 1], 1);
		closeall(mini);
	}
	else if (mini->p == o && !str[mini->p + 1])
	{
		if (ta == 1)
			return;
		// printf("%d\n", mini->fd[2 * (mini->p - 1)]);
		dup2(mini->fd[2 * (mini->p - 1)], 0);
		closeall(mini);
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
	}
	else if (i == 3)
	{
		mini->fd[1] = open(str, O_WRONLY | O_APPEND | O_CREAT, 0644);
		dup2(mini->fd[1], 1);
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
		if (ft_strncmp(str[j], "<<\0", 3) == 0)
		{
			if (setinfile(str[j + 1], mini, 2) == 0)
					return (1);
		}
		else if (ft_strncmp(str[j], "<\0", 2) == 0)
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

int		check_quote_redir(t_vars* mini, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			mini->redir++;
			return (0);
		}
		i++;
	}
	return (1);
}

void	codifiqing(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			j++;
		if (str[i] == '>' && j % 2 != 0)
			str[i] = '\a';
		else if (str[i] == '<' && j % 2 != 0)
			str[i] = '\b';
		else if (str[i] == '|' && j % 2 != 0)
			str[i] = '\t';
		i++;
	}
}
	
int	forredirectout(char ***str, t_vars *mini)
{
	int	j;
	int	ta;

	j = 0;
	ta = 0;
	if (ft_countwords(mini->input, ' ') == 1)
		return (0);
	while (str[mini->p][j])
		j++;
	j--;
	while (j > 0 && str[mini->p][j] && ft_strncmp(str[mini->p][j], ">", 1) != 0)
		j--;
	if (str[mini->p][j] && ft_strncmp(str[mini->p][j], ">>", 2) == 0)
	{
		if (str[mini->p][j + 1])
		{
			if (setinfile(str[mini->p][j + 1], mini, 3) == 0)
				ta = 1;
			else
				return (-100);
		}
	}
	else if (str[mini->p][j] && ft_strncmp(str[mini->p][j], ">", 1) == 0)
	{
		if (str[mini->p][j + 1])
		{
			if (setinfile(str[mini->p][j + 1], mini, 1) == 0)
				ta = 1;
			else
				return (-100);
		}
	}
	if (numpipe(mini->input) > 0)
		piping(str, mini, ta);
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

char	*convert_exit_code(t_vars *mini)
{
	char	*converted;
	
	converted = ft_itoa(mini->exit_code);
	return (converted);
}

void	expr_jesus(char **nao, t_vars *mini)
{
    int i = 0;

    if (ft_strncmp(nao[0], "expr", 4) == 0)
    {
        while (nao[i] != NULL)
        {
            if (ft_strncmp(nao[i], "$?", 2) == 0)
            {
                free(nao[i]);
                nao[i] = convert_exit_code(mini);
            }
            i++;
        }
    }
}

int	decide(char **str, t_vars *mini)
{
	mini->i = findbuiltimatrix(str, mini);
	if (mini->i == -2)
		mini->i = findcmdinmatrix(str, mini);
	if (mini->i == -1)
	{
		if (findmistake(str) == -1)
			return (3);
		de_codifiqing(str[findmistake(str)]);
		ft_printf("%s: command not found\n", str[findmistake(str)]);
		mini->exit_code = 127;
		return (2);
	}
	else if (mini->i == -15)
		return (1);
	return (0);
}

void	killchild(char ***str, t_vars *mini)
{
	int	i;

	i = -1;
	
	while (str[++i])
		free_split(str[i]);
	free(str);
	free(mini->fd);
	free_env_export(mini);
	exit(4);
}

void	comandddd(char ***str, t_vars *mini)
{
	char	*sim;
	char	**nao;
	int		i;

	i = decide(str[mini->p], mini);
	if (i == 1)
		return ;
	mini->pid = fork();
	if (mini->pid == 0)
	{
		if (i != 0)
			killchild(str, mini);
		child_signals_handler();
		if (forredirect(str[mini->p], mini) < 0 || forredirectout(str, mini) < 0)
			killchild(str, mini);
		if (checkbuiltin(mini) == 0)
			killchild(str, mini);
		sim = ft_strjoin("/", str[mini->p][mini->i]);
		checkpath(sim, mini);
		nao = findflags(str[mini->p], mini->i);
		expr_jesus(nao, mini);
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
}

int	checkinput(t_vars *mini)
{
	char	***tudo = paodelosplit(mini->input, numpipe(mini->input));
	mini->trueflag = ft_split(mini->input, '|');
	int		i;
	int		status;

	mini->p = 0;
	i = -1;
	if (tudo == NULL || mini->trueflag == NULL)
		return (2);
	fdfd(mini);
	while (mini->p <= numpipe(mini->input) && numpipe(mini->input) >= 0)
	{
		if (mini->check != NULL)
		{
			free(mini->check);
			mini->check = NULL;
		}
		if (tudo[mini->p])
			comandddd(tudo, mini);
		mini->p++;
	}
	while (tudo[++i])
		free_split(tudo[i]);
	free(tudo);
	closeall(mini);
	free(mini->fd);
	while (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			mini->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mini->exit_code = 128 + WTERMSIG(status);
	}
	return (0);
}

int	find_echo(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == ' ' && str[i + 1] == 'e' && str[i + 2] == 'c' &&
		str[i + 3] == 'h' && str[i + 4] == 'o' && str[i + 5] == ' ') ||
		(str[i] == 'e' && str[i + 1] == 'c' &&
		str[i + 2] == 'h' && str[i + 3] == 'o' && str[i + 4] == ' '))
			return (0);
		i++;
	}
	return (1);
}

char	*antimalucos(char *str)
{
	int		i;
	int		a;
	char	*s;

	a = 0;
	i = 0;
	if (find_echo(str) == 0)
		return (str);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '<' || str[i + 1] == '>')
			{
				if (str[i + 2] == '<' || str[i + 2] == '>')
					return (NULL);
				i ++;
			}
			a += 2;
		}
		if (str[i] == '|')
			a += 2;
		i++;
	}
	s = malloc(sizeof(char) * (i + a + 1));
	if (!s)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	a = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			s[a] = ' ';
			a++;
			if (str[i + 1] == '<' || str[i + 1] == '>')
			{
				s[a] = str[i];
				i++;
				a++;
				s[a] = str[i];
				i++;
				a++;
				s[a] = ' ';
				a++;
			}
			else
			{
				s[a] = str[i];
				a++;
				i++;
				s[a] = ' ';
				a++;				
			}

		}
		if (str[i] == '|')
		{
			s[a] = ' ';
			a++;
			s[a] = str[i];
			a++;
			i++;
			s[a] = ' ';
			a++;
		}
		s[a] = str[i];
		i++;
		a++;
	}
	s[a] = '\0';
	free(str);
	return (s);
}

int	antisegfault(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

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
		mini->input = readline(RED "bash> " R);
		if (!mini->input)
			break;
		if (ft_strlen(mini->input) > 0 && antisegfault(mini->input) == 0)
		{
			add_history(mini->input);
			mini->input = antimalucos(mini->input);
			if (mini->input)
			{
				codifiqing(mini->input);
				mini->input = quotescrazy(mini->input);
				if (mini->input == NULL)
					printf("Quote error\n");
				else
					checkinput(mini);
			}
			free(mini->input);
		}
	}
	exit_value = mini->exit_code;
	free_env_export(mini);
	return (exit_value);
}
