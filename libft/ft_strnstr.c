/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 17:29:55 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/03 23:44:20 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Locates the first occurrence of the null-terminated string 'needle' in
**	the string 'haystack', where not more than len characters are searched.
**	Characters that appear after a `\0' character are not searched.
**	If 'needle' is an empty string, 'haystack' is returned; if 'needle' occurs
**	nowhere in 'haystack', NULL is returned; otherwise a pointer to the first
**	character of the first occurrence of 'needle' is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	j;

	if (!*needle)
		return ((char*)haystack);
	while (*haystack && len-- > 0)
	{
		j = 0;
		while (haystack[j] == needle[j] && j++ <= len)
			if (!needle[j])
				return ((char*)haystack);
		haystack++;
	}
	return (0);
}
