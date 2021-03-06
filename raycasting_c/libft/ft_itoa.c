/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkal <mkal@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 21:32:11 by mkal              #+#    #+#             */
/*   Updated: 2020/10/07 02:53:31 by mkal             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strrev(char *s)
{
	size_t	i;
	size_t	j;
	int		c;

	i = 0;
	j = ft_strlen(s);
	while (j-- > i)
	{
		c = s[j];
		s[j] = s[i];
		s[i] = c;
		i++;
	}
	return (s);
}

static int	ft_itoa_len(int n)
{
	int	count;

	count = (n <= 0) ? 1 : 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	char	*nbr;
	size_t	i;
	size_t	neg;

	neg = (n < 0) ? 1 : 0;
	if (!(nbr = (char*)ft_calloc(ft_itoa_len(n) + 1, sizeof(char))))
		return (0);
	if (n == 0)
		nbr[0] = '0';
	i = 0;
	while (n)
	{
		nbr[i++] = (n % 10 < 0 ? -(n % 10) : n % 10) + '0';
		n /= 10;
	}
	if (neg)
		nbr[i] = '-';
	return (ft_strrev(nbr));
}
