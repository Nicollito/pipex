/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:15:22 by nimadela          #+#    #+#             */
/*   Updated: 2025/03/31 16:58:49 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				nbr;
	unsigned char	*s1_temp;
	unsigned char	*s2_temp;

	i = 0;
	s1_temp = (unsigned char *)s1;
	s2_temp = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (s1_temp[i] && s2_temp[i] && s1_temp[i] == s2_temp[i] && i < n - 1)
		i++;
	nbr = s1_temp[i] - s2_temp[i];
	return (nbr);
}
