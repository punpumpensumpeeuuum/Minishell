/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinda-si <dinda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:12:21 by dinda-si          #+#    #+#             */
/*   Updated: 2023/10/16 16:40:15 by dinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*n;
	t_list	*h;

	h = NULL;
	if (!lst)
		return (0);
	while (lst)
	{
		n = ft_lstnew(f(lst->content));
		if (!n)
		{
			ft_lstclear(&h, del);
			return (0);
		}
		ft_lstadd_back(&h, n);
		lst = lst->next;
	}
	return (h);
}
