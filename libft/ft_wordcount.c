/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:29:07 by jpizarro          #+#    #+#             */
/*   Updated: 2020/01/30 21:13:24 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Splitting the string 's' using the character 'c' as a delimiter, returns
**	the number of group of characters (words) resulting in the string 's'.
*/

#include "libft.h"

size_t	ft_wordcount(const char *s, char c)
{
	size_t i;

	i = 0;
	while (*s)
		if (*s++ != c && (*s == c || !*s))
			i++;
	return (i);
}
