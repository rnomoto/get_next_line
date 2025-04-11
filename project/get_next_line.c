/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/11 15:41:59 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //for debugging

char *put_stock(int fd, char *stock, int *flag)
{
	static int fd_check = -2;
	char *ret;
	size_t i;
	size_t j;

	i = 0;
	//printf("fd_check: %d\n", fd_check);
	ret = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	//ret = NULL;
	if (ret == NULL)
		return NULL;
	ret = ft_memset(ret, 0, (BUFFER_SIZE + 1));
	while (fd == fd_check && i < ft_strlen(stock))  //if stock == NULL ?
	{
		//printf("stock: %zu\n", ft_strlen(stock));
		ret[i] = stock[i];
		j = 0;
		while (ret[i] == '\n' || ret[i] == '\0')
		{
			//printf("stock[j]: '%c'\n", stock[j]);
			stock[j] = stock[i + j + 1];
			if (stock[j] == '\0')
			{
				//flag ?
				*flag = 1;
				return ret;
			}
			j++;
		}
		i++;
	}
	//printf("stock is empty\n");
	stock = ft_memset(stock, 0, BUFFER_SIZE + 1);
	fd_check = fd;
	//printf("ret: \"%s\"\n", ret);
	return ret;
}

char *put_read(int fd, char *ret, char *stock)
{
	char *read_buf;
	ssize_t read_size;
	ssize_t i;
	ssize_t j;
	ssize_t k;
	size_t count;

	i = 0;
	j = 0;
	k = 0;
	count = 1;
	read_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	//read_buf == NULL;
	if (read_buf == NULL)
		return NULL;
	read_buf = ft_memset(read_buf, 0, (BUFFER_SIZE + 1));
	while (1)
	{
		j = 0;
		read_size = read(fd, read_buf, BUFFER_SIZE);
		//printf("read_size: %zd\n", read_size);
		//printf("read_buf: \"%s\"\n", read_buf);
		if (read_size <= 0 && count == 1)
		{
			free(read_buf);
			free(ret);
			return NULL;
		}
		else if (read_size == 0 && count != 1)
		{
			free(read_buf);
			return ret;
		}
		ret = strdup_double(ret, ((BUFFER_SIZE + 1) * count));
		//printf("dupret: \"%s\"\n", ret);
		if (ret == NULL)
		{
			free(read_buf);
			return NULL;
		}
		while (ret[i] != '\0')
			i++;
		while (j < read_size)
		{
			ret[i] = read_buf[j];
			//j++;
			while (ret[i] == '\n' && j < read_size)
			{
				j++;
				stock[k] = read_buf[j];
				//j++;
				k++;
			}
			i++;
			j++;
		}
		//printf("dupret: \"%s\"\n", ret);
		if (k != 0)
		{
			free(read_buf);
			return ret;
		}
		count++;
	}
	free(read_buf);
	return ret;
}

char	*get_next_line(int fd)
{
	static char	stock[BUFFER_SIZE + 1];
	//static int flag = 0;
	int *flag;
	char *ret;
	//printf("fd: %d\n", fd);
	flag = (int *)malloc(sizeof(int) * 1);
	if (flag == NULL)
		return NULL;
	*flag = 0;
	ret = put_stock(fd, stock, flag);
	//printf("ret: \"%s\"\n", ret);
	//ret = NULL;
	if (ret == NULL)
	{
		free(flag);
		return (NULL);
	}
	//printf("flag: %d\n", *flag);
	if (*flag == 1)
	{
		free(flag);
		return (ret);
	}
	
	ret = put_read(fd, ret, stock);
	//printf("ret: \"%s\"\n", ret);
	//ret = NULL;
	if (ret == NULL)
	{
		free(flag);
		free(ret);
		return (NULL);
	}
	free(flag);
	return (ret);
}
