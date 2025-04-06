/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:52:59 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/06 16:50:08 by rnomoto          ###   ########.fr       */
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

char *double_buffer(char *old_buf, size_t size)
{
    char *new_buf;
    size_t i = 0;

    new_buf = (char *)ft_calloc(sizeof(char), size * 2);
    if (new_buf == NULL)
        return (NULL);
    while (i < size)
    {
        new_buf[i] = old_buf[i];
        i++;
    }
    free(old_buf);
    return new_buf;
}

int read_c(int fd)
{
    char c;
    ssize_t read_check;

    read_check = read(fd, &c, 1);
    if (read_check == -1 || read_check == 0)
        return -1;

    return c;
}