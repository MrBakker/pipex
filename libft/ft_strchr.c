/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 14:08:11 by jbakker       #+#    #+#                 */
/*   Updated: 2023/10/06 14:59:56 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*output;

	output = (unsigned char *)s;
	c = (unsigned char)c;
	while (*output != c && *output)
		++output;
	if (*output == c)
		return ((char *)output);
	return (0);
}
