/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charindex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 20:13:01 by jpizarro          #+#    #+#             */
/*   Updated: 2020/06/07 20:19:19 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Finds the first ocurrence of the character 'c' in the string 'str'.
**	Returns the index of 'c' in "str", or -1 if 'c' is not found.
*/

int		ft_charindex(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (s[i] ? i : -1);
}
