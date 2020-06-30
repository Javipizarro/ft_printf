/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:03:45 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/01 03:32:27 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Writes len bytes of value 'c' (converted to an unsigned char)
**	to the string 'b'. Returns its first argument.
*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*j;

	j = b;
	while (len-- > 0)
		*j++ = (unsigned char)c;
	return (b);
}
