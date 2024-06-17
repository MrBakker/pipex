/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 16:35:25 by jbakker       #+#    #+#                 */
/*   Updated: 2023/10/04 16:16:21 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	size_t			str_len;
	char			*output;

	index = 0;
	str_len = ft_strlen(s);
	output = (char *)malloc((str_len + 1) * sizeof(char));
	if (!output)
		return (0);
	while (index < str_len)
	{
		output[index] = (*f)(index, s[index]);
		++index;
	}
	output[index] = '\0';
	return (output);
}
