/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 08:31:56 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/01 02:45:38 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Writes 'n' zeroed bytes to the string 's'.  If 'n' is zero, bzero() does
**	nothing.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char *j;

	j = s;
	while (n-- > 0)
		*(j++) = 0;
}
