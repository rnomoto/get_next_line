/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:52:59 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/09 18:13:06 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

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

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
		index++;
	return (index);
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

ssize_t	find_enter(char *str, ssize_t size)
{
	ssize_t	i;

	i = 0;
	while ((str[i] != '\n' && str[i] != '\0') && i < size)
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
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

char	*recursive_gnl(int fd, char *ret, char *buf_store)
{
	char	*read_buf;
	ssize_t	read_size;

	ret = double_buffer(ret, ft_strlen(ret));
	if (ret == NULL)
		return (NULL);
	read_buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (read_buf == NULL)
	{
		free(ret);
		return (NULL);
	}
	read_size = read(fd, read_buf, BUFFER_SIZE);
	if (read_size == -1)
	{
		free(ret);
		free(read_buf);
		return (NULL);
	}
	else if (read_size == 0)
	{
		free(read_buf);
		return (ret);
	}
	ret = put_line(fd, ret, read_buf, buf_store, read_size);
	return (ret);
}

char	*cat_store(int fd, char *buf_store)
{
	char		*ret;
	static int	fd_check = 2;
	char *buf_store_copy;

	if (fd == fd_check)
	{
		ret = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + ft_strlen(buf_store)
				+ 1);
		if (ret == NULL)
			return (NULL);
		if (find_enter(buf_store, ft_strlen(buf_store)) != -1)
		{
			ft_strlcat(ret, buf_store, find_enter(buf_store, ft_strlen(buf_store)) + 2);
			buf_store += find_enter(buf_store, ft_strlen(buf_store)) + 1;
		}
		ft_strlcat(ret, buf_store, ft_strlen(buf_store) + 1);
	}
	else
	{
		fd_check = fd;
		ret = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (ret == NULL)
			return (NULL);
	}
	ft_bzero(buf_store, BUFFER_SIZE);
	return (ret);
}

char	*put_line(int fd, char *ret, char *buf, char *buf_store,
		ssize_t read_size)
{
	ssize_t	enter_pos;

	enter_pos = find_enter(buf, read_size);
	if (enter_pos != -1)
	{
		ft_strlcat(ret, buf, ft_strlen(ret) + enter_pos + 2);
		ft_strlcat(buf_store, buf + enter_pos + 1, read_size - enter_pos + 1);
	}
	else
	{
		ft_strlcat(ret, buf, ft_strlen(ret) + read_size + 1);
		ret = recursive_gnl(fd, ret, buf_store);
	}
	free(buf);
	return (ret);
}
