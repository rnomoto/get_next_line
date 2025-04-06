/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/06 17:34:16 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd)
{
    char *buf;
    char c;
    size_t i = 0;
    size_t buf_size = 10;
    
    c = 'a'; //initiate
    buf = (char *)ft_calloc(sizeof(char), buf_size + 1);
    if (buf == NULL)
        return NULL;
    while (c != '\n')
    {
        if (i == buf_size)
        {
            buf = double_buffer(buf, buf_size);
            if (buf == NULL)
                return NULL;
            buf_size *= 2;
        }
        c = read_c(fd);
        if (c == -1 && i == 0)
        {
            free(buf);
            return NULL;
        }
        else if (c == -1)
            break;
        buf[i] = c;
        i++;
    }
    return buf;
}
