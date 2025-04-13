/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:52:59 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/13 11:30:13 by rnomoto          ###   ########.fr       */
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

// if mem == NULL? impossible
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

char	*strdup_double(char *mem, size_t *old_size)
{
	char	*new_mem;
	size_t new_size;

	//new_mem = (char *)malloc(sizeof(char) * (*old_size * 2));
	new_size = *old_size + BUFFER_SIZE;
	new_mem = (char *)malloc(sizeof(char) * new_size);
	if (new_mem == NULL)
	{
		free(mem);
		return (NULL);
	}
	ft_memset(new_mem, '\0', new_size);
	ft_strlcpy(new_mem, mem, ft_strlen(mem) + 1);
	*old_size = new_size;
	//free(mem);
	return (new_mem);
}
