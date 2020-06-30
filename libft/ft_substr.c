/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 19:53:41 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/03 19:46:11 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Allocates (with malloc(3)) and returns a substring from the string 's'
**	or NULL if the allocation fails. The substring begins at index 'start'
**	and is of maximum size 'len'.
*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	str[len + 1];
	size_t	slen;

	if (!s)
		return (NULL);
	if (start > (slen = ft_strlen(s)))
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	ft_memcpy(str, s + start, len + 1);
	str[len] = 0;
	return (ft_strdup(str));
}
