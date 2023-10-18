/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbohling <fbohling@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:43:20 by fbohling          #+#    #+#             */
/*   Updated: 2023/08/25 17:42:16 by fbohling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	substr_numb(char *temp, char c)
{
	size_t	numb;
	size_t	i;

	i = 0;
	numb = 0;
	if (temp[0] != c)
	{
		i = 1;
		numb++;
	}
	while (temp[i])
	{
		if ((i == 0 || temp[i - 1] == c) && temp[i] != c)
			numb++;
		i++;
	}
	return (numb);
}

void	copy(const char *s, char *arr, size_t start, size_t count)
{
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	while (i < start + count)
	{
		arr[j] = s[i];
		i++;
		j++;
	}
	arr[j] = '\0';
}

char	**word_len(char *temp, char c, char **arr)
{
	size_t	i;
	size_t	count;
	size_t	y;

	i = 0;
	count = 0;
	y = 0;
	while (temp[i] != '\0')
	{
		if (temp[i] != c)
			count++;
		i++;
		if ((temp[i] == c || !temp[i]) && count > 0)
		{
			arr[y] = ft_calloc((count + 1), sizeof(char));
			copy(temp, arr[y], i - count, count);
			y++;
			count = 0;
		}
	}
	arr[y] = NULL;
	return (arr);
}

char	**ft_split_without_delimiter(char *s)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 2);
	arr[0] = ft_strdup(s);
	arr[1] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	numb;

	if (!s)
		return (NULL);
	if (*s == '\0')
	{
		arr = (char **)malloc(sizeof(char *));
		arr[0] = NULL;
		return (arr);
	}
	if (!ft_strchr(s, c))
	{
		arr = ft_split_without_delimiter((char *)s);
		return (arr);
	}
	numb = substr_numb((char *)s, c);
	arr = ft_calloc(1 + numb, sizeof(char *));
	if (!arr)
		return (NULL);
	arr = word_len((char *)s, c, arr);
	return (arr);
}
