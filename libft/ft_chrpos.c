/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 00:46:27 by jpizarro          #+#    #+#             */
/*   Updated: 2020/05/22 13:11:33 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Finds the first ocurrence of the character 'c' in the string 'str'.
**	Returns the possition of 'c' in "str" (NOT the index of 'c' in "str"),
**	or 0 if 'c' is not found.
*/

int		ft_chrpos(char const *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (s[i] ? ++i : 0);
}
