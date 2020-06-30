/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:57:04 by jpizarro          #+#    #+#             */
/*   Updated: 2020/05/22 11:40:00 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Deletes and frees the given element and every successor of that element,
**	using the function 'del' and free(3).
**	Finally, the pointer to the list must be set to NULL.
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	while (*lst && del)
	{
		ft_lstdelone(*lst, del);
		*lst = (*lst)->next;
	}
}

/*
**	Si no pasara el test, probar metiendo después del while:
**	*lst = NULL;
**	y si todavía no, hacer una aux para almacenar el puntero next.
*/
