/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 18:56:24 by jpizarro          #+#    #+#             */
/*   Updated: 2020/06/01 02:44:41 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Allocates (with malloc(3)) and returns a string representing the
**	signed long integer received as 'n' transformed acording to the
**	base received as 'base' or NULL if the allocation fails.
**	Negative numbers are also handled.
*/

#include "libft.h"

char	*ft_itoa_base(int n, char *base)
{
	char		ret[34];
	short int	i;
	short int	neg;
	int			bsize;

	if (!base || (bsize = ft_strlen(base)) < 2)
		return ("Error, no valid base to transform 'n'");
	i = 33;
	ret[i] = 0;
	if (n < 0)
	{
		neg = 1;
		ret[--i] = base[-(n % bsize)];
		n = -(n / bsize);
	}
	while (n % bsize || n / bsize)
	{
		ret[--i] = base[n % bsize];
		n /= bsize;
	}
	if (neg == 1)
		ret[--i] = '-';
	else if (i == 33)
		ret[--i] = '0';
	return (ft_strdup(&ret[i]));
}
