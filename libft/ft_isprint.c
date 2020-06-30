/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:14:21 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/01 18:30:08 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Tests for any printing character, including space (` '). Which is between
**	decimals 32 and 126.
*/

int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}
