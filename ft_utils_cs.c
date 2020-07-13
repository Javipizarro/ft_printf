/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_cs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:29:28 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 16:30:01 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Prints the char 'c' once applied the changes
**	specified in the t_convspecs struct pointed by *cs.
**	Returns the number of characters printed.
*/

int			ft_spec_c(t_convspecs *cs, char c)
{
	int		padd;

	padd = 0;
	if (cs->adj == '-')
		write(1, &c, 1);
	while (++padd < cs->width)
		if (cs->padd == '0' && !cs->adj)
			write(1, "0", 1);
		else
			write(1, " ", 1);
	if (!cs->adj)
		write(1, &c, 1);
	return (padd);
}

/*
**	Prints the string 's' once applied the changes expecified in
**	the t_convspecs struct pointed by *cs.
**	Returns the number of characters printed.
*/

int			ft_spec_s(t_convspecs *cs, char *s)
{
	int		padd;
	int		len;

	s = !s ? "(null)" : s;
	len = ft_strlen(s);
	len = cs->pre >= 0 && cs->pre < len ? cs->pre : len;
	if (cs->adj == '-')
		write(1, s, len);
	padd = 0;
	while (cs->width-- > len && ++padd)
		write(1, &cs->padd, 1);
	if (!cs->adj)
		write(1, s, len);
	return (len + padd);
}
