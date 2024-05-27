/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:21:42 by dinda-si          #+#    #+#             */
/*   Updated: 2024/05/27 23:14:51 by elemesmo         ###   ########.fr       */
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
	int		fd[2];
	int		pid;
	int		i;
}	t_vars;

int		inputnum(char *input);
void	redirect(t_vars *mini);
char	*checkpath(char *cmd1, char **env);
int		numpipe(char *str);
char	**ft_goodsplit(char	*str);

#endif