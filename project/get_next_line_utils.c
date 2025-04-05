/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:52:59 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/05 19:51:26 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdint.h>

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

int ft_getc(int fd)
{
    static char buf[BUFSIZ]; //how to allocate buffer
    static int fd_store = -2;
    static ssize_t read_size;
    static int i = 0;

    if (fd_store == fd)
        i++;
    else
    {
        i = 0;
        read_size = read(fd, buf, sizeof buf); 
        if (read_size == -1)
            return EOF;
        else if (read_size == 0)
            return EOF;
        fd_store = fd;
    }
    if (read_size == 0)
        return EOF;
    read_size --;
    return buf[i];
}