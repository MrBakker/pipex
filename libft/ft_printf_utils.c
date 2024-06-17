/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 14:58:19 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/02 12:10:02 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	num_to_hex(int num, char base_case)
{
	return ((num < 10) * '0' + (num > 9) * (base_case - 10) + num);
}

int	ft_max(int a, int b)
{
	return ((a > b) * a + (b >= a) * b);
}
