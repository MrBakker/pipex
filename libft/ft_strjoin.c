/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 15:13:27 by jbakker       #+#    #+#                 */
/*   Updated: 2023/10/04 16:16:03 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*output;
	int		str_index;
	int		out_index;

	str_index = 0;
	out_index = 0;
	output = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!output)
		return (0);
	while (s1[str_index])
		output[out_index++] = s1[str_index++];
	str_index = 0;
	while (s2[str_index])
		output[out_index++] = s2[str_index++];
	output[out_index] = '\0';
	return (output);
}
