/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:26:57 by athirion          #+#    #+#             */
/*   Updated: 2021/11/26 10:05:44 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (str)
	{
		i = 0;
		while (s[i])
		{
			str[i] = (*f)(i, s[i]);
			i ++;
		}
		str[i] = '\0';
	}
	return (str);
}
