/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 23:47:31 by jpizarro          #+#    #+#             */
/*   Updated: 2020/06/02 06:14:47 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Allocates (with malloc(3)) and returns a string representing the integer
**	received as an argument or NULL if the allocation fails.
**	Negative numbers are also handled.
*/

#include "libft.h"

char	*ft_itoa(int n)
{
	char	str[12];
	int		i;
	int		neg;

	i = 11;
	str[i] = 0;
	neg = 0;
	if (!n)
		str[--i] = '0';
	if (n < 0)
	{
		neg = 1;
		str[--i] = '0' - n % 10;
		n /= -10;
	}
	while (n % 10 || n / 10)
	{
		str[--i] = n % 10 + '0';
		n /= 10;
	}
	if (neg)
		str[--i] = '-';
	return (ft_strdup(&str[i]));
}
