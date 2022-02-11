/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:28:22 by athirion          #+#    #+#             */
/*   Updated: 2021/11/26 10:06:35 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			len;
	int				i;
	unsigned char	uc;

	uc = (unsigned char) c;
	len = ft_strlen(s);
	i = (int)len;
	while (i >= 0)
	{
		if (s[i] == uc)
			return ((char *)(s + i));
		i --;
	}
	return (0);
}
