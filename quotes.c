/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elemesmo <elemesmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:55:39 by elemesmo          #+#    #+#             */
/*   Updated: 2024/07/01 16:57:08 by elemesmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotescrazy(char *input, int i, int nq)
{
	char	q;
	int		pq;

	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			q = input[i];
			pq = i;
			i++;
			nq = 1;
			while (input[i] && input[i] != q)
				i++;
			if (input[i] == q && nq == 1)
			{
				input[i] = ' ';
				input[pq] = ' ';
				nq = 0;
			}
		}
		i++;
	}
	if (nq == 1)
		return (NULL);
	return (input);
}
