/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/09 18:13:55 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	buf_store[BUFFER_SIZE];
	char		*ret;
	char		*buf;
	ssize_t		read_size;

    printf("store: %s\n", buf_store);
	ret = cat_store(fd, buf_store);
	if (ret == NULL)
		return (NULL);
    buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
    if (buf == NULL)
    {
        free(ret);
        return (NULL);
    }
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size <= 0)
	{
		free(buf);
		free(ret);
		return (NULL);
	}
	ret = put_line(fd, ret, buf, buf_store, read_size);
	return (ret);
}
