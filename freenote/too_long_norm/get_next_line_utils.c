/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:49:06 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/23 18:07:53 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

ssize_t	find_char(const char *str, int c)
{
	ssize_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (str[i] == c)
		return (i);
	return (-1);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	check;

	i = 0;
	check = ft_strlen(src);
	if (size == 0)
		return (check);
	while (src[i] != '\0' && size > 1)
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	dst[i] = '\0';
	return (check);
}

void	*ft_memset(void *mem, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem_cast;
	unsigned char	c_cast;

	i = 0;
	mem_cast = (unsigned char *)mem;
	c_cast = (unsigned char)c;
	while (i < n)
	{
		mem_cast[i] = c_cast;
		i++;
	}
	return (mem_cast);
}

char	*alloc_cpy(char *mem, size_t size)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * size); //null ok
	if (ret == NULL)
	{
		free(mem);
		return (NULL);
	}
	ft_memset(ret, '\0', size);
	if (mem == NULL)
		return (ret);
	ft_strlcpy(ret, mem, ft_strlen(mem) + 1);
	free(mem);
	return (ret);
}
