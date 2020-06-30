/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 06:04:31 by jpizarro          #+#    #+#             */
/*   Updated: 2020/06/02 06:13:56 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Allocates (with malloc(3)) and returns a string representing the unsigned
**	integer received as an argument or  NULL if the allocation fails.
*/

#include "libft.h"

char	*ft_uitoa(unsigned int n)
{
	char		str[12];
	short int	i;

	i = 11;
	str[i] = 0;
	if (!n)
		str[--i] = '0';
	while (n % 10 || n / 10)
	{
		str[--i] = n % 10 + '0';
		n /= 10;
	}
	return (ft_strdup(&str[i]));
}
