/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:18:44 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/01 02:49:57 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Copies bytes from string 'src' to string 'dst'.  If the character 'c' (as
**	converted to an unsigned char) occurs in the string 'src', the copy stops
**	and a pointer to the byte after the copy of 'c' in the string dst is
**	returned.  Otherwise, 'n' bytes are copied, and a NULL pointer is returned.
*/

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	s = src;
	d = dst;
	while (n-- > 0)
	{
		*d++ = *s;
		if (*s++ == (unsigned char)c)
			return (d++);
	}
	return (0);
}
