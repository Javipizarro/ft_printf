/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 06:16:51 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 15:09:48 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Writes 'n' 'c' valued bytes to the string 's' and ends it with a 0.
**  Note that 's' must be at least 'n + 1' characters long, so it has space
**  for the 0 ending character. If 'n' is zero, ft_bchar() makes 's'
**  an empty string.
*/

#include "libft.h"

void	ft_bchar(char *s, size_t len, char c)
{
	while (len-- > 0)
		*(s++) = c;
	*s = 0;
}
