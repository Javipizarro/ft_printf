/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 17:14:28 by jpizarro          #+#    #+#             */
/*   Updated: 2020/05/25 17:18:24 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Copies 'n' bytes from memory area 'src' to memory area 'dst'. If 'dst' and
**	'src' overlap, behavior is undefined. Returns the original value of 'dst'.
*/

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char *s;
	unsigned char		*d;

	if (dst == src || !n)
		return (dst);
	if (dst || src)
	{
		s = src;
		d = dst;
		while (n-- > 0)
			*(d++) = *(s++);
		return (dst);
	}
	return (0);
}
