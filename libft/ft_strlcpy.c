/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 20:47:04 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/01 18:29:31 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Copies up to 'dstsize' - 1 characters from the string 'src' to 'dst',
**	NUL-terminating the result if 'dstsize' is not 0. Takes the full size of
**	the destination buffer and guarantee nul-termination if there is room.
**	Note that room for the nul should be included in 'dstsize'.
**	If the 'src' and 'dst' strings overlap, the behavior is undefined.
*/

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	if (dstsize)
	{
		i = -1;
		while (dstsize-- && src[++i])
			dst[i] = src[i];
		dst[i] = 0;
	}
	return (ft_strlen(src));
}
