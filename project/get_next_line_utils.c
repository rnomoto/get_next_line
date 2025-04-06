/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:52:59 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/06 19:01:29 by rnomoto          ###   ########.fr       */
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
	new_buf = (char *)ft_calloc(sizeof(char), new_size);
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
