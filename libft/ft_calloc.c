/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 17:38:09 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/05 18:57:09 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Allocates enough space in memory for 'count' objects that are 'size'
**	bytes of memory each and returns a pointer to the allocated memory.
**	The allocated memory is filled with bytes of value zero.
*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *mem;

	if (!(mem = malloc(count * size)))
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}
