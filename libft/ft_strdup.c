/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 18:08:53 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/05 19:02:25 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Allocates sufficient memory for a copy of the string s1, does the copy,
**	and returns a pointer to it.  The pointer may subsequently be used as an
**	argument to the function free(3).
*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char *s;

	if (!(s = malloc(ft_strlen(s1) + 1)))
		return (NULL);
	ft_memcpy(s, s1, ft_strlen(s1) + 1);
	return (s);
}
