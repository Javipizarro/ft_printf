/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:23:41 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/01 02:55:06 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Copies 'len' bytes from string 'src' to string 'dst'. The two strings
**	may overlap; the copy is always done in a non-destructive manner.
**	Returns the original value of dst.
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char *s;
	unsigned char		*d;

	s = src;
	d = dst;
	if (s > d)
		while (len-- > 0)
			*(d++) = *(s++);
	else if (s < d)
		while (len-- > 0)
			*(d + len) = *(s + len);
	return (dst);
}
