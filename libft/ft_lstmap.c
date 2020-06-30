/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 17:16:26 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/07 17:33:25 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Iterates the list ’lst’ and applies the function 'f' to the content
**	of each element. Creates and returns a new list resulting of the
**	successive applications of the function 'f'. The 'del' function is
**	used to delete the content of an element if needed.
**	It returns NULL if the allocation fails.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*head;

	if (!lst || !f || !(new = ft_lstnew(f(lst->content))))
		return (NULL);
	head = new;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		new = new->next;
	}
	new->next = NULL;
	return (head);
}
