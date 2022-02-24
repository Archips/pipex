/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:46:44 by athirion          #+#    #+#             */
/*   Updated: 2021/11/27 14:36:38 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				index;
	unsigned char	uc;

	index = 0;
	uc = (unsigned char) c;
	while (s[index])
	{
		if (s[index] == uc)
			return ((char *)(s + index));
		index ++;
	}
	if (s[index] == '\0' && uc == '\0')
		return ((char *)(s + index));
	return (0);
}
