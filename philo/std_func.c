/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:26:19 by fbohling          #+#    #+#             */
/*   Updated: 2023/08/25 14:55:06 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_philo(const char *str)
{
	int	r;
	int	s;

	s = 1;
	r = 0;
	if (str[0] == '\0')
		return (0);
	while ((*str >= '\t' && *str <= '\r') || *str == 32)
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '-' || *str == '+')
		str++;
	conversion(str, &r, &s);
	return ((int)(r * s));
}

void	conversion(const char *str, int *result, int *sign)
{
	int	digit;

	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (*sign == 1 && (*result > INT_MAX / 10
				|| (*result == INT_MAX / 10 && digit > INT_MAX % 10)))
		{
			printf("\033[1;31mEXCEEDING MAX INT\031\n");
			exit (1);
		}
		else if (*sign == -1 && (*result > -(INT_MIN / 10)
				|| (*result == -(INT_MIN / 10) && digit > -(INT_MIN % 10))))
		{
			printf("\033[1;31mEXCEEDING MIN INT\031\n");
			exit (1);
		}
		*result = *result * 10 + digit;
		str++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != '\0')
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	if ((char)c == '\0')
		return (ptr);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;

	dest = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, (char *)s1, ft_strlen(s1) + 1);
	ft_strlcat(dest, (char *)s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*temp;
	size_t	len_dst;
	size_t	len_src;
	size_t	i;
	size_t	ret;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	temp = (char *)src;
	i = 0;
	if (len_dst < dstsize)
		ret = (len_dst + len_src);
	else
		ret = (len_src + dstsize);
	while (temp[i] && (len_dst + 1) < dstsize)
	{
		dst[len_dst] = temp[i];
		len_dst++;
		i++;
	}
	dst[len_dst] = '\0';
	return (ret);
}
