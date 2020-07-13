/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 16:35:15 by jpizarro          #+#    #+#             */
/*   Updated: 2020/07/13 16:35:20 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	Receives the string s apply the specs adj, sign and padd, and prints
**	the result.
**	Returns the number of characters printed.
*/

int			ft_printer(t_convspecs *cs, char *s)
{
	int		add;
	int		len;

	add = 0;
	len = ft_strlen(s);
	cs->width -= cs->sign ? 1 : 0;
	cs->width -= cs->spec == 'p' || cs->alt ? 2 : 0;
	add += cs->spec == 'p' || cs->alt ? 2 : 0;
	if (cs->sign && (cs->adj || cs->padd == '0') && ++add)
		write(1, &cs->sign, 1);
	if ((cs->adj || cs->padd == '0') && (cs->spec == 'p' || cs->alt))
		write(1, cs->spec == 'X' ? "0X" : "0x", 2);
	if (cs->adj == '-')
		write(1, s, len);
	while (cs->width-- > len && ++add)
		write(1, &cs->padd, 1);
	if (cs->sign && !cs->adj && cs->padd == ' ' && ++add)
		write(1, &cs->sign, 1);
	if (!cs->adj && cs->padd == ' ' && (cs->spec == 'p' || cs->alt))
		write(1, cs->spec == 'X' ? "0X" : "0x", 2);
	if (!cs->adj)
		write(1, s, len);
	return (len + add);
}
