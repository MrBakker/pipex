/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <marvin@42.fr>                       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 17:02:13 by jbakker       #+#    #+#                 */
/*   Updated: 2023/10/06 14:44:47 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	char	*trim;
	int		output;
	int		factor;

	output = 0;
	factor = 1;
	trim = (char *)nptr;
	while ((*trim >= 9 && *trim <= 13) || *trim == ' ')
		trim++;
	if (*trim == '-' && ft_isdigit(*(trim + 1)))
	{
		++trim;
		factor = -1;
	}
	if (*trim == '+')
		++trim;
	while (*trim && ft_isdigit(*trim))
	{
		output = output * 10 + (*trim - '0') * factor;
		++trim;
	}
	return (output);
}
