/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:26:08 by jpizarro          #+#    #+#             */
/*   Updated: 2020/02/01 02:23:54 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Converts an upper-case letter to the corresponding lower-case letter.
*/

#include "libft.h"

int		ft_tolower(int c)
{
	return (ft_isupper(c) ? c + 32 : c);
}
