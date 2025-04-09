/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/09 14:47:15 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

ssize_t find_enter(char *str, ssize_t size)
{
    ssize_t i = 0;

    while((str[i] != '\n' && str[i] != '\0') && i < size)
        i++;   
    if (str[i] == '\n')
        return i;
    return -1;
}

char *recursive_gnl(int fd, char *ret, char *buf_store)
{
    char *read_buf;
    ssize_t read_size;
    ssize_t enter_pos;

    printf("%zu\n", ft_strlen(ret));
    ret = double_buffer(ret, ft_strlen(ret));
    if (ret == NULL)
        return NULL;
    read_buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
    if (read_buf == NULL)
    {
        free(ret);
        return NULL;
    }
    read_size = read(fd, read_buf, BUFFER_SIZE);
    if (read_size == -1)
    {
        free(ret);
        free(read_buf);
        return NULL;
    }
    else if (read_size == 0)
    {
        free(read_buf);
        return ret;
    }
    enter_pos = find_enter(read_buf, read_size);
    if (enter_pos != -1)
    {
        ft_strlcat(ret, read_buf, ft_strlen(ret) + enter_pos + 2);
        ft_strlcat(buf_store, read_buf + enter_pos, read_size - enter_pos);
    }
    else
    {
        ret = recursive_gnl(fd, ret, buf_store);
    }
    free(read_buf);
    return ret;
}

char *get_next_line(int fd)
{
    static int fd_check = 2;
    static char buf_store[BUFFER_SIZE];
    char *ret;
    char *buf;
    ssize_t read_size;
    ssize_t enter_pos;
    
    if (fd == fd_check)
    {
        ret = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + ft_strlen(buf_store) + 1);
        if (ret == NULL)
            return NULL;
        ft_strlcat(ret, buf_store, ft_strlen(buf_store) + 1);
    }
    else
    {
        fd_check = fd;
        ret = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
        if (ret == NULL)
            return NULL;
    }
    //buf_store = ft_memset(buf_store, 0, BUFFER_SIZE);
    ft_bzero(buf_store, BUFFER_SIZE);
    buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
    if (buf == NULL)
    {
        free(ret);
        return NULL;
    }
    read_size = read(fd, buf, BUFFER_SIZE);
    if (read_size <= 0)
    {
        free(buf);
        free(ret);
        return NULL;
    }
    enter_pos = find_enter(buf, read_size);
    printf("enter: %zd\n", enter_pos);
    // printf("%s", ret);
    // printf("%zd", enter_pos);
    if (enter_pos != -1)
    {
        ft_strlcat(ret, buf, ft_strlen(ret) + enter_pos + 2);
        ft_strlcat(buf_store, buf + enter_pos + 1, read_size - enter_pos + 1);
    }
    else
        ret = recursive_gnl(fd, ret, buf_store);
    free(buf);
    return ret; 
}
