/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:21:42 by dinda-si          #+#    #+#             */
/*   Updated: 2024/06/07 18:28:13 by dinda-si         ###   ########.fr       */
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
# include <limits.h>

typedef struct s_vars
{
	char	**env;
	char	**export;
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
	int		env_len;
}	t_vars;

// parsing
void	alreadyprog(t_vars *mini);
int		numpipe(char *str);
int		inputnum(char *input);
void	**arrangegoodsplit(t_vars *mini);

// path
int		fastcheckpath(t_vars *mini, int flag, int i);
char	*checkpath(char *cmd1, char **env);
int		getpipepath(char **trueflag, t_vars *mini);
char	*findcmdplace(char *str, char **env);

// split
int		wordllllen(char const *s, char c);
int		checkimportant(char *s);
void	redirect(t_vars *mini, char *str);
char	**ft_goodsplit(char	*str);

// execute
void	allocfd(int p, t_vars *mini);
void	closeall(t_vars *mini);
void	execute(t_vars *mini, int i, int p);
void	executeone(t_vars *mini);
void	veryexecute(t_vars *mini, int i);

// builtin env
void	init_env(char **env, t_vars *mini);
int		env_builtin(t_vars *mini);

// builtin export
void	init_export(t_vars *mini);
int		export_builtin(t_vars *mini);
void	swap_strings(char **a, char **b);
void	sorting_export(t_vars *mini);
void	free_split(char **str);

// builtin exit
int		not_number(char *str);
void	exit_anyways(char **str);
int		exit_builtin(t_vars *mini);

// builtin echo
int		echo_builtin(t_vars *mini);
int		is_flag(char *str);

#endif