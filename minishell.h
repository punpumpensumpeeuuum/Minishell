/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:21:42 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/11 17:34:59 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\e[0;31m"
# define R   "\001\e[0m\002"

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <limits.h>
# include <string.h>

typedef struct s_vars
{
	char	*input;
	// builtins
	char	**env;
	char	**new_env;
	char	**export;
	char	**new_export;
	int		exp_len;
	int		env_len;
	int		flag_env;
	// paths
	char	**flag;
	char	**trueflag;
	char	**allpaths;
	char	*check;
	// parsing
	char	*redrct;
	int		flagfdin;
	int		flagfdout;
	int		*fd;
	int		pid;
	int		i;
	int		p;
	int		redir;
	// heredoc
	char	**limiters;
	int		heredoc_on;
	// exit
	int		exit_code;
	int		running;
}	t_vars;

// parsing
int		numpipe(char *str);
int		inputnum(char *input);
void	arrangegoodsplit(t_vars *mini);
int		getpipepath(char **trueflag, t_vars *mini);
char	*trimtrimtrim(char *str, int i);
int		ft_checkprint(char *str);

int		checkbuiltin(t_vars *mini);
int		truecheckbuilt(char *str);
int		findbuiltimatrix(char **str, t_vars *mini);
int		findmistake(char **str);
int		truecheckbuilt(char *str);

// path
int		fastcheckpath(t_vars *mini, int flag, int i);
void	checkpath(char *cmd, t_vars *mini);
void	checkhelp(char *comand, char **env, int i, t_vars *mini);
int		findcmdplace(char *input, t_vars *mini);
int		findcmdinmatrix(char **puzle, t_vars *mini);

// execute
void	closeall(t_vars *mini);

// builtin env
void	init_env(char **env, t_vars *mini);
void	env_builtin(t_vars *mini);
void	env_update(t_vars *mini, char *str);
void	create_env(t_vars *mini);
void	free_first_string(char **arr);
void	shlvl_update(t_vars *mini);
t_vars 	*init_mini(void);

// builtin export
void	init_export(t_vars *mini);
int		export_builtin(t_vars *mini);
void	swap_strings(char **a, char **b);
void	sorting_export(t_vars *mini);
void	free_split(char **str);
int		export_len(char **str);
int     export_check(char *str);
void    export_var(t_vars *mini);
void	export_update1(t_vars *mini);
void	export_update(t_vars *mini, char *str);
void	exp_update1(t_vars *mini);
void	exp_update(t_vars *mini, char *str);
int		export_redircheck(char *str);
void	print_export(t_vars *mini);

// builtin exit
int		not_number(char *str);
void	exit_anyways(char **str);
int		exit_builtin(t_vars *mini);

// builtin echo
int		echo_builtin(t_vars *mini);
int		is_flag(char *str);
int		dollar_flag(char *str);
void	echo_dollar_finish(char *str, int k, t_vars *mini);
int		echo_compare(const char *s1, const char *s2);
char	*take_equal(char *str);
void	dollar_quote(t_vars *mini, char *str);
int		dollar_flag_count(char *str);
void	echo_special(t_vars *mini, char *str);
int		echo_quote(char *str);
void	de_codifiqing(char *str);

//builtin cd
int		find_var(t_vars *mini, char *to_find);
void	get_pwds(t_vars *mini);
void	in_directory(char *directory, t_vars *mini);
char	*ft_getenv( t_vars *mini, char	*to_find);
void	cd_1_arg(t_vars *mini);
void	cd_2_args(t_vars *mini);
void	cd_builtin(t_vars *mini);
int		cd_special_1(t_vars *mini);

//quotes.c
int		check_quotes(char *input);
void    remove_single_quote(char *cmd);
void    remove_double_quote(char *cmd);
char    *quotescrazy(char *input);
void    quote_together(char *cmd);

//builtin unset
int		unset_builtin(t_vars *mini);
void	pwd_builtin(void);

//heredoc.c
int		count_limiters(char **split);
void	free_array(char **array);
void	heredoc_lim_array(t_vars *mini);
void	heredoc_input(int fd, char **limiters, t_vars *mini);
void	fork_error(void);
void	heredoc_child(char **limiters, t_vars *mini);
void	creat_pipe(int fd[2]);
int		heredoc(t_vars *mini);
char	*heredoc_dollar_finish(char *str, int k, t_vars *mini);
void	heredoc_expander(int fd, char *line, t_vars *mini);

// free.c
void	free_double_array(char **str, t_vars *mini);
void	free_env_export(t_vars *mini);
void	free_fd(int p, t_vars *mini);

// signals.c
void    sigint_handler(int sig);
void    signal_heredoc(int sig);
void    signals_handler(void);
void    child_handler(int signal);
void    child_signals_handler(void);

#endif