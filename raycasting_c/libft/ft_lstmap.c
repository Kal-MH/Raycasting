/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 00:19:10 by mkal              #+#    #+#             */
/*   Updated: 2020/10/07 03:33:43 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_cur;
	t_list	*tmp;

	if (!lst || !f)
		return (0);
	if (!(new_lst = ft_lstnew(f(lst->content))))
		return (0);
	new_cur = new_lst;
	lst = lst->next;
	while (lst)
	{
		if (!(tmp = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		new_cur->next = tmp;
		new_cur = tmp;
		lst = lst->next;
	}
	return (new_lst);
}
