/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:21:42 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/31 17:31:18 by dinda-si         ###   ########.fr       */
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

// split
int		checkimportant(char *s);
int		inputnum(char *input);
void	redirect(t_vars *mini, char *str);
char	*checkpath(char *cmd1, char **env);
int		numpipe(char *str);
char	**ft_goodsplit(char	*str);

// execute
void	allocfd(int	p, t_vars *mini);
void	execute(t_vars *mini, char **env, int i);
void	executeone(t_vars *mini, char **env);

#endif