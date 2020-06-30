/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 15:08:51 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/03 21:09:37 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Locates the first occurrence of c (converted to a char) in the
**	string pointed to by s. The terminating null character is
**	considered to be part of the string; therefore if c is `\0',
**	the functions locate the terminating `\0'.
**  Returns a pointer to the located character, or NULL if the
**  character does not appear in the string.
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
		if (*s++ == (char)c)
			return ((char*)--s);
	if (!c)
		return ((char*)s);
	return (0);
}
