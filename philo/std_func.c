/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:26:19 by fbohling          #+#    #+#             */
/*   Updated: 2023/10/20 12:03:55 by fbohling         ###   ########.fr       */
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
	if (!conversion(str, &r, &s))
		return (-1);
	return ((int)(r * s));
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

void	ft_putstr(char *s)
{
	size_t	i;
	int		c;

	if (s == NULL)
	{
		write(1, "(null)", 6);
		return ;
	}
	i = 0;
	while (s[i])
	{
		c = (int)s[i];
		write (1, &c, 1);
		i++;
	}
}
