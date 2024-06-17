/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 13:43:55 by jbakker       #+#    #+#                 */
/*   Updated: 2023/10/04 13:56:08 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*ptr;

	ptr = *lst;
	if (lst && *lst && del)
	{
		while (ptr)
		{
			*lst = ptr->next;
			ft_lstdelone(ptr, del);
			ptr = *lst;
		}
	}
}
