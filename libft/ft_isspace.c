/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:06:43 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/02 16:40:12 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Tests for the white-space characters. For any locale, this includes
**	the following standard characters: `\t' `\n' `\v' `\f' `\r' ` '.
**	Returns zero if the character tests false and returns non-zero if the
**	character tests true.
*/

int		ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n' ||
			c == '\r' || c == '\t' || c == '\v');
}
