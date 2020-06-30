/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:32:47 by jpizarro          #+#    #+#             */
/*   Updated: 2020/06/06 19:45:03 by jpizarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*s;
	
	if (!s1 || !s2)
		return (NULL);
	s = ft_strjoin(s1, s2);
	free(s1);
	s1 = NULL;
	free(s2);
	s2 = NULL;
	return (s);
}