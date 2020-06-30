/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:30:23 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/02 17:05:10 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Tests for a decimal digit character. Regardless of locale, this includes
**	the following characters only: `0' `1' `2' `3' `4' `5' `6' `7' `8' `9'.
**	Returns zero if 'c' tests false and return non-zero if 'c' tests true.
*/

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
