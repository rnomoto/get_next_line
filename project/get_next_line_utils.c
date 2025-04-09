/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:52:59 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/09 14:21:13 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	index;
	size_t	count;
	char	*tmp;

	count = nmemb * size;
	if ((size != 0 && nmemb != 0) && SIZE_MAX / nmemb < size)
		return (NULL);
	else if (size == 0 || nmemb == 0)
		count = 1;
	index = 0;
	tmp = (char *)malloc(count);
	if (tmp == NULL)
		return (NULL);
	while (index < count)
	{
		tmp[index] = 0;
		index++;
	}
	return (tmp);
}

char	*double_buffer(char *old_buf, size_t size)
{
	char	*new_buf;
	size_t	i;
	size_t	new_size;

	i = 0;
	new_size = size * 2;
	new_buf = (char *)ft_calloc(sizeof(char), new_size + 1);
	if (new_buf == NULL)
		return (NULL);
	while (i < size)
	{
		new_buf[i] = old_buf[i];
		i++;
	}
	free(old_buf);
	return (new_buf);
}

int	read_c(int fd)
{
	char	c;
	ssize_t	read_check;

	read_check = read(fd, &c, 1);
	if (read_check == -1 || read_check == 0)
		return (-1);
	return (c);
}

char	*put_line(char *buf, size_t size, int fd)
{
	char	c;
	size_t	i;

	i = 0;
	c = 'a';
	while (c != '\n')
	{
		if (i == size - 1)
		{
			buf = double_buffer(buf, size);
			if (buf == NULL)
				return (NULL);
			size *= 2;
		}
		c = read_c(fd);
		if (c == -1 && i == 0)
		{
			free(buf);
			return (NULL);
		}
		else if (c == -1)
			break ;
		buf[i] = c;
		i++;
	}
	return (buf);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	if (size == 0 && dest == NULL)
		dest_len = 0;
	else
		dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dest_len)
		return (src_len + size);
	else
	{
		while (dest[i] != '\0')
			i++;
		while (i + 1 < size && *src)
		{
			dest[i] = *src;
			i++;
			src++;
		}
		dest[i] = '\0';
	}
	return (dest_len + src_len);
}

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
}

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			index;
	unsigned char	*str_cast;
	unsigned char	c_cast;

	index = 0;
	str_cast = (unsigned char *)str;
	c_cast = (unsigned char)c;
	while (index < n)
	{
		str_cast[index] = c_cast;
		index++;
	}
	return (str_cast);
}

void	ft_bzero(void *str, size_t n)
{
	size_t			index;
	unsigned char	*str_cast;

	index = 0;
	str_cast = (unsigned char *)str;
	while (index < n)
	{
		str_cast[index] = 0;
		index++;
	}
}