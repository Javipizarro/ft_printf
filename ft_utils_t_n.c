/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_t_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:32:53 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 16:44:17 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Allocates (with malloc(3)) and creates a new t_n double linked list
**	object in the space pointed by 'prev', and stores the number 'n'
**	of character read in nchr.
*/

t_n			*ft_newn(t_n *prev, int nchr)
{
	t_n		*new;

	if (!(new = malloc(sizeof(t_n))))
		return (NULL);
	new->prev = prev;
	new->arg = NULL;
	new->nchr = nchr;
	new->next = NULL;
	return (new);
}

/*
**	Given a valid link in a t_n list, it traverses the whole chain,
**	from first to last link, assigning the nchar values to the variables
**	pointed by arg and freeing the links as it goes.
*/

int			ft_asignn(t_n *current)
{
	int n;

	n = current->nchr;
	while (current->prev)
		current = current->prev;
	while (current->arg)
	{
		*(current->arg) = current->nchr;
		current = current->next;
		free(current->prev);
	}
	free(current);
	current = NULL;
	return (n);
}

/*
**	Along with the nchr value in the link of the chain t_n, saves pointer to the
**	variable where it will be stored at the end of the ft_printf() execution.
**	Creates a new link and copies the current nchr value to it in order to keep
**	counting in the new link the number of characters printed by ft_printf().
*/

void		ft_saven(t_n **n, va_list args, t_convspecs *cs)
{
	if (cs->len == 'H')
		(*n)->arg = (long long int*)va_arg(args, signed char*);
	else if (cs->len == 'h')
		(*n)->arg = (long long int*)va_arg(args, short int*);
	else if (!cs->len)
		(*n)->arg = (long long int*)va_arg(args, int*);
	else if (cs->len == 'l')
		(*n)->arg = (long long int*)va_arg(args, long int*);
	else if (cs->len == 'L')
		(*n)->arg = (long long int*)va_arg(args, long long int*);
	(*n)->next = ft_newn(*n, (*n)->nchr);
	*n = (*n)->next;
}
