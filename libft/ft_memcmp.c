/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:25:50 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/01 03:01:57 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Compares byte string 's1' against byte string 's2.'	Both strings are
**	assumed to be 'n' bytes long. Returns zero if the two strings are
**	identical, otherwise returns the difference between the first two
**	differing bytes (treated as unsigned char values).
*/

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *t1;
	const unsigned char *t2;

	t1 = s1;
	t2 = s2;
	while (n-- > 0)
		if (*t1++ != *t2++)
			return (*--t1 - *--t2);
	return (0);
}
