/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/06 20:56:07 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*get_next_line(int fd)
// {
// 	char	*buf;
// 	size_t	buf_size;

// 	buf_size = 10;
// 	buf = (char *)ft_calloc(sizeof(char), buf_size);
// 	if (buf == NULL)
// 		return (NULL);
// 	buf = put_line(buf, buf_size, fd);
// 	return (buf);
// }

ssize_t new_line_check(char *str)
{
    ssize_t i = 0;

    while(str[i] != '\n' || str[i] == '\0')
    {
        i++;   
    }
    return i;
}

char *get_next_line(int fd)
{
    char *buf;
    char *ret;
    ssize_t read_check;
    ssize_t cut_pos = 0;
    
    // allocate a first buffer
    buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
    if (buf == NULL)
        return NULL;
    // read BUFFER_SIZE bytes
    read_check = read(fd, buf, BUFFER_SIZE);
    if (read_check <= 0)
    {
        free(buf);
        return NULL;
    }
    // search ENTER in the buffer
    cut_pos = new_line_check(buf);
    ret = (char *)ft_calloc(sizeof(char), cut_pos + 2);
    if (ret == NULL)
        return NULL;
    // if : the buffer has ENTER
    while (cut_pos < BUFFER_SIZE - 1)
    {
        *ret = *buf;
        ret++;
        buf++;
        cut_pos--;
    }
    // else if : the buffer has no ENTER
    // if(cut_pos == BUFFER_SIZE - 1)
    //     ret = get_next_line(fd);
    return ret;
}
