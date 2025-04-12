/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/12 18:55:37 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //for debugging

char *put_stock(int fd, char *stock, char *ret)
{
	static int fd_check = -2;
	ssize_t enter_pos;
	char *tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(stock) + 1));
	//tmp = NULL;
	if (tmp == NULL)
		return NULL;
	if (fd == fd_check)
	{
		//printf("stock: %s\n", stock);
		ft_strlcpy(tmp, stock, (ft_strlen(stock) + 1));
		enter_pos = find_char(stock, '\n');
		if (enter_pos != -1)
		{
			ft_strlcpy(ret, tmp, (enter_pos + 2));
			ft_strlcpy(stock, (tmp + enter_pos + 1), ft_strlen(tmp + enter_pos + 1) + 1);
			//printf("stock2: %s\n", stock);
			free(tmp);
			return ret;
		}
		ft_strlcpy(ret, tmp, (ft_strlen(stock) + 1));
		//printf("stock3: %s\n", stock);
	}
	ft_memset(stock, '\0', ft_strlen(stock) + 1);
	fd_check = fd;
	free(tmp);
	//printf("ret1: \"%p\"\n", ret);
	return ret;
}

ssize_t read_buf(int fd, char *buf, char **ret_p)
{
    ssize_t read_size;
    char *tmp_free;
    size_t total;

    read_size = read(fd, buf, BUFFER_SIZE);
	//printf("buf_read: %s\n", buf);
    if (read_size == 0 && buf[0] == '\0')
        return 0;
    else if (read_size <= 0)
        return -1;
    // if ((ft_strlen(ret) + (size_t)read_size + 1) > sizeof(ret))
    total = ft_strlen(*ret_p) + (size_t)read_size + 1;
	//printf("ret2: \"%p\"\n", *ret_p);
    if (total > sizeof(*ret_p))
    {
        tmp_free = *ret_p;
		//printf("ret2.5: \"%p\"\n", *ret_p);
        *ret_p = strdup_double(*ret_p, sizeof(*ret_p));
		//printf("ret3: \"%p\"\n", *ret_p);
        if (*ret_p == NULL)
        {
            free(tmp_free);
            return -1;
        }
    }
    return read_size;
}

int put_buf(char **ret_p, char *buf, char *stock, ssize_t read_size)
{
    ssize_t enter_pos;

    enter_pos = find_char(buf, '\n');
    //printf("enter_pos: %zd\n", enter_pos);
	//printf("buf: %s\n", buf);
    if (enter_pos == -1 && read_size == BUFFER_SIZE)
	{
		//printf("ret: \"%s\"\n", *ret_p);
        ft_strlcpy((*ret_p + ft_strlen(*ret_p)), buf, (read_size + 1));
	}
    else
    {
        if (enter_pos == -1)
            ft_strlcpy((*ret_p + ft_strlen(*ret_p)), buf, (read_size + 1));
        else
        {
			//debug
			//printf("ret: \"%p\"\n", *ret_p);
            ft_strlcpy((*ret_p + ft_strlen(*ret_p)), buf, (enter_pos + 2));
            if (read_size == BUFFER_SIZE)
                ft_strlcpy(stock, (buf + enter_pos + 1), (read_size - enter_pos));
        }
        return 0;
    }
    return 1;
}

char *read_put(int fd, char *ret, char *stock)
{
    char *buf;
    ssize_t read_size;
    int put_check;
	char **ret_p;

	ret_p = &ret;
    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    //buf = NULL;
    if (buf == NULL)
        return NULL;
    ft_memset(buf, '\0', (BUFFER_SIZE + 1));
    while (1)
    {
        read_size = read_buf(fd, buf, ret_p);
        //printf("read_size: %zd\n", read_size);
		//printf("ret4: \"%p\"\n", ret);
        if (read_size <= 0)
            break;
        put_check = put_buf(ret_p, buf, stock, read_size);
        //printf("put_check: %d\n", put_check);
        if (put_check <= 0)
            break;
    }
    //printf("read_size: %zd\n", read_size);
    free(buf);
    if (read_size == 0 || put_check == 0)
        return ret;
    return NULL;
}

char	*get_next_line(int fd)
{
	static char	stock[BUFFER_SIZE + 1];
	char *ret;
	char *tmp;

	ret = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	//ret = NULL;
	if (ret == NULL)
		return NULL;
	ft_memset(ret, '\0', (BUFFER_SIZE + 1));
	tmp = ret;
	ret = put_stock(fd, stock, ret);
	//ret = NULL;
	if (ret == NULL)
	{
		free(tmp);
		return NULL;
	}
	ret = read_put(fd, ret, stock);
	tmp = ret; // for free previous ret if new_ret == NULL
	// ret = NULL;
	if (ret == NULL)
	{
		free(tmp);
		return (NULL);
	}
	return (ret);
}
