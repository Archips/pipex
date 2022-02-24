/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athirion <athirion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 22:11:25 by athirion          #+#    #+#             */
/*   Updated: 2021/11/26 10:01:21 by athirion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cpy;
	t_list	*temp;

	cpy = *lst;
	while (cpy)
	{
		temp = cpy->next;
		ft_lstdelone(cpy, del);
		cpy = temp;
	}
	*lst = NULL;
}
