/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:14:28 by jomendes          #+#    #+#             */
/*   Updated: 2024/11/22 18:46:15 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// void	process_echo_arguments(char **split, t_vars *mini, int i)
// {
// 	int	in_quotes;

// 	in_quotes = 0;
// 	while (split[i])
// 	{
// 		if (split[i][0] == '\'' && split[i][ft_strlen(split[i]) - 1] == '\'')
// 		{
// 			// remove_single_quote(split[i]);
// 			ft_printf("%s", split[i]);
// 		}
// 		else if (split[i][0] == '"' && split[i][ft_strlen(split[i]) - 1] == '"')
// 		{
// 			// remove_double_quote(split[i]);
// 			// handle_double_quotes(split[i], mini);
// 		}
// 		else if (split[i][0] == '"' || split[i][0] == '\''
// 				|| split[i][ft_strlen(split[i]) - 1] == '"'
// 				|| split[i][ft_strlen(split[i]) - 1] == '\'')
// 			// handle_mixed_quotes(split[i], &in_quotes);
// 		else
// 			handle_normal_case(mini, split[i]);
// 		if (split[i + 1])
// 			ft_printf(" ");
// 		i++;
// 	}
// }

// void	handle_double_quotes(char *str, t_vars *mini)
// {
// 	if (echo_quote(str) == 1)
// 		echo_special(mini, str);
// 	else if (str[0] == '$')
// 		echo_dollar_finish(str, 1, mini, 0);
// 	else
// 		ft_printf("%s", str);
// }

// void	handle_mixed_quotes(char *str, int *in_quotes)
// {
// 	remove_double_quote(str);
// 	remove_single_quote(str);
// 	*in_quotes = 1;
// 	if (str[ft_strlen(str) - 1] == '"' || str[ft_strlen(str) - 1] == '\'')
// 	{
// 		*in_quotes = 0;
// 		return ;
// 	}
// 	ft_printf("%s", str);
// }

// void	handle_normal_case(t_vars *mini, char *str)
// {
// 	if (str[0] == '$')
// 	{
// 		if (str[1] == '?')
// 			ft_printf("%d", g_exit_code);
// 		else
// 			echo_dollar_finish(str, 1, mini, 0);
// 	}
// 	else
// 		ft_printf("%s", str);
// }
