/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: jomendes <jomendes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:21:42 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/14 14:06:41 by jomendes         ###   ########.fr       */
=======
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:21:42 by dinda-si          #+#    #+#             */
/*   Updated: 2024/11/14 16:10:41 by gneto-co         ###   ########.fr       */
>>>>>>> norminette
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\e[0;31m"
# define R "\001\e[0m\002"

# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <string.h>
# include <sys/wait.h>

extern int	g_exit_code;

typedef struct s_vars
{
	char	*input;
	// builtins
	char	**env;
	char	**new_env;
	char	**export;
	char	**new_export;
	int		env_len;
	int		exp_len;
	int		flag_env;
	// paths
	// char	**flag;
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
	int		total_lim;
	int		heredoc_on;
	// exit
	int		exit_code;
	int		running;
}			t_vars;

// cd_builtin.c
void		cd_builtin(t_vars *mini);
void		cd_2_args(t_vars *mini);
void		cd_1_arg(t_vars *mini);
int			cd_special_1(t_vars *mini);

// cd_builtin1.c
int			find_var(t_vars *mini, char *to_find);
char		*ft_getenv(t_vars *mini, char *to_find);
void		get_pwds(t_vars *mini);
void		in_directory(char *directory, t_vars *mini);

// echo_builtin.c
int			echo_builtin(t_vars *mini);
void		echo_special(t_vars *mini, char *str);
void		echo_dollar_finish(char *str, int k, t_vars *mini);

// echo_builtin1.c
int			echo_quote(char *str);
char		*take_equal(char *str);
int			dollar_flag_count(char *str);
int			dollar_flag(char *str);
int			is_flag(char *str);

// env_builtin.c
void		env_update(t_vars *mini, char *str);
void		env_builtin(t_vars *mini);
void		init_env(char **env, t_vars *mini);

// env_buiultin1.c
void		envvv_update(t_vars *mini, char *str);
void		envvv_update1(t_vars *mini);
void		free_first_string(char **arr);
void		create_env(t_vars *mini);
void		shlvl_update(t_vars *mini);

// export_builtin.c
void		init_export(t_vars *mini);
int			export_builtin(t_vars *mini);
void		export_var(t_vars *mini);
int			env_check(char *str);

// export_builtin1.c
void		exp_update(t_vars *mini, char *str);
void		export_update1(t_vars *mini);
void		export_update(t_vars *mini, char *str);

// export_utils.c
void		swap_strings(char **a, char **b);
void		sorting_export(t_vars *mini);
int			export_check(char *str);
int			str_compare(char *s1, char *s2);

// pipes_redir.c
void		piping(char ***str, t_vars *mini, int ta);
int			setinfile(char *str, t_vars *mini, int i);
int			forredirect(char **str, t_vars *mini);
int			forredirectout(char ***str, t_vars *mini);

// heredoc1.c
void		heredoc_input(int fd, char **limiters, t_vars *mini);
void		add_limiter(t_vars *mini, char **split, int *i, int *j);
void		heredoc_lim_array(t_vars *mini);
void		heredoc_child(char **limiters, t_vars *mini);

// heredoc_utils.c
void		creat_pipe(int fd[2]);
void		fork_error(void);
void		heredoc_expander(int fd, char *line, t_vars *mini);
int			count_limiters(char **split);

// heredoc.c
char		*heredoc_dollar_finish(char *str, int k, t_vars *mini);
void		heredoc_dollar_finish_help(t_vars *mini, char *result, char *str,
				char *real_result);
void		heredoc_dollar_finish1(char *result, char *str, char *real_result);
int			heredoc(t_vars *mini);
int			heredoc1(int fdin, int status);

// execution1.c
char		**findflags(char **str, int i);
int			checkbuiltin(t_vars *mini);
char		*expand(char *str, t_vars *mini);

// execution.c
<<<<<<< HEAD
int		checkinput(t_vars *mini);
void	check_input1(t_vars *mini, char ***tudo);
void	fdfd(t_vars *mini);
char	***paodelosplit(char *str, int pipes, int i);
int		decide(char **str, t_vars *mini);
void	comandddd(char ***str, t_vars *mini);
=======
int			checkinput(t_vars *mini);
void		fdfd(t_vars *mini);
char		***paodelosplit(char *str, int pipes, int i);
int			decide(char **str, t_vars *mini);
void		comandddd(char ***str, t_vars *mini);
>>>>>>> norminette

// utils_again.c
int			ft_strcmp(const char *s1, const char *s2);
void		codifiqing(char *str);
void		de_codifiqing(char *str);
int			check_quote_redir(t_vars *mini, char *str);
char		*convert_exit_code(void);

// evenmoreutils.c
int			more(char *input, int i);
int			findmistake(char **str);
char		*trimtrimtrim(char *str, int i);
char		*trimhelp(char *str, int i, int a, int start);
int			ft_checkprint(char *str);

// moreutils.c
int			truecheckbuilt(char *str);
int			findbuiltimatrix(char **str, t_vars *mini);
int			findcmdinmatrix(char **puzle, t_vars *mini);
int			findcmdplace(char *input, t_vars *mini);

// utils.c
int			numpipe(char *str);
void		redirect(t_vars *mini, char *str);
int			inputnum(char *input);
int			getpipepath(char **trueflag, t_vars *mini);
int			wordllllen(char const *s, char c);

// parsing.c
<<<<<<< HEAD
int		antisegfault(char *str);
int		porfavor(char *str, int i, int k);
char	*antimalucos(char *str, int i, int a);
int		find_echo(char *str);
=======
int			antisegfault(char *str);
int			porfavor(char *str, int i, int k, int a);
char		*antimalucos(char *str, int i, int a);
int			find_echo(char *str);
>>>>>>> norminette

// path
void		checkpath(char *cmd, t_vars *mini);
void		checkhelp(char *comand, char **env, int i, t_vars *mini);

// builtin exit
int			not_number(char *str);
void		exit_anyways(char **str);
int			exit_builtin(t_vars *mini);

// quotes.c
int			check_quotes(char *input);
void		remove_single_quote(char *cmd);
void		remove_double_quote(char *cmd);
char		*quotescrazy(char *input);

// builtin unset
int			unset_builtin(t_vars *mini);
void		pwd_builtin(void);

// free.c
void		killchild(char ***str, t_vars *mini);
void		free_env_export(t_vars *mini);
void		free_env_export1(t_vars *mini);
void		free_array(char **array);
void		free_split(char **str);

// free1.c
void		free_double_array(char **str, int len);
void		closeall(t_vars *mini);
void		free_fd(int p, t_vars *mini);
void		free_split(char **str);

// signals.c
void		sigint_handler(int sig);
void		signal_heredoc(int sig);
void		signals_handler(void);
void		child_handler(int signal);
void		child_signals_handler(void);
t_vars		*get_mini(void);

#endif