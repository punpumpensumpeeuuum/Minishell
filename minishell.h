/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:21:42 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/02 23:03:42 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_vars
{
	char	*input;
	char	**flag;
	char	**trueflag;
	char	*cmdt;
	char	*check;
	char	*redrct;
	int		cmdplace;
	int		flagfd;
	int		*fd;
	int		pid;
	int		i;
}	t_vars;

// path
int		fastcheckpath(t_vars *mini, char **env, int flag, int i);
char	*checkpath(char *cmd1, char **env);

// split
int		wordllllen(char const *s, char c);
int		checkimportant(char *s);
int		inputnum(char *input);
void	redirect(t_vars *mini, char *str);
int		numpipe(char *str);
char	**ft_goodsplit(char	*str);

// execute
void	allocfd(int p, t_vars *mini);
void	execute(t_vars *mini, char **env, int i);
void	executeone(t_vars *mini, char **env);
void	veryexecute(t_vars *mini, char **env, int i);

#endif