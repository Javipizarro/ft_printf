/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:46:30 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/01 02:30:07 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Tests for an ASCII character, which is any character between 0 and
**	decimal 127 inclusive.
*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
