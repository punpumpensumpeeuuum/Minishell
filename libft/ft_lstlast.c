/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:34:33 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/16 15:28:16 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ultinmo;

	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	ultinmo = lst;
	return (ultinmo);
}
/*
int	main(void)
{
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;

	node1 = malloc(sizeof(t_list));
	node2 = malloc(sizeof(t_list));
	node3 = malloc(sizeof(t_list));
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	ft_lstlast(node1);
	return (0);
}*/
