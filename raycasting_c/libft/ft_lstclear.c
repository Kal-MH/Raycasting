/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 00:11:38 by mkal              #+#    #+#             */
/*   Updated: 2020/10/07 00:16:02 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		cur = (*lst);
		(*lst) = (*lst)->next;
		ft_lstdelone(cur, del);
	}
}
