/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wordcount.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 13:49:42 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/15 15:27:46 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_wordcount(char *ptr)
{
	int	count;
	int	index;

	index = 0;
	count = 0;
	while (ptr[index])
	{
		while (ptr[index] && ptr[index] == ' ')
			index++;
		if (!ptr[index])
			break ;
		++count;
		while (ptr[index] && ptr[index] != ' ')
			index++;
	}
	return (count);
}
