/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:33:39 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/01 02:21:59 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Converts a lower-case letter to the corresponding upper-case letter.
*/

#include "libft.h"

int		ft_toupper(int c)
{
	return (ft_islower(c) ? c - 32 : c);
}
