/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/11 17:02:41 by rnomoto          ###   ########.fr       */
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
	ret = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (ret == NULL)
	{
		return NULL;
	}
	ret = ft_memset(ret, 0, (BUFFER_SIZE + 1));
	while (fd == fd_check && i < ft_strlen(stock))  //if stock == NULL? impossible
	{
		ret[i] = stock[i];
		j = 0;
		while (ret[i] == '\n' || ret[i] == '\0')
		{
			stock[j] = stock[i + j + 1];
			if (stock[j] == '\0')
			{
				*flag = 1;
				return ret;
			}
			j++;
		}
		i++;
	}
	stock = ft_memset(stock, 0, BUFFER_SIZE + 1);
	fd_check = fd;
	return ret;
}


//split?
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
	if (read_buf == NULL)
	{
		free(ret);
		return NULL;
	}
	read_buf = ft_memset(read_buf, 0, (BUFFER_SIZE + 1));
	while (1)
	{
		j = 0;
		read_size = read(fd, read_buf, BUFFER_SIZE);
		if (read_size <= 0)
		{
			free(read_buf);
			if (read_size == 0 && count != 1)
				return ret;
			free(ret); //else if(read_size <= 0 && count == 1)
			return NULL;
		}
		// if (read_size <= 0 && count == 1)
		// {
		// 	free(read_buf);
		// 	free(ret);
		// 	return NULL;
		// }
		// else if (read_size == 0 && count != 1)
		// {
		// 	free(read_buf);
		// 	return ret;
		// }
		ret = strdup_double(ret, ((BUFFER_SIZE + 1) * count));
		char *tmp = ret; //for free if allcate occurs error
		//ret = NULL;
		if (ret == NULL)
		{
			free(tmp);
			free(read_buf);
			return NULL;
		}
		while ((j + k) < read_size)
		{
			if (ret[i] != '\0')
				i++;
			else if (read_buf[j] != '\n')
			{
				ret[i] = read_buf[j];
				j++;
			}
			else
			{
				if (k == 0)
					ret[i] = read_buf[j];
				stock[k] = read_buf[j + k];
				k++;
			}
		}
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
	int *flag;
	char *ret;
	
	flag = (int *)malloc(sizeof(int) * 1);
	if (flag == NULL)
		return NULL;
	*flag = 0;
	ret = put_stock(fd, stock, flag);
	if (ret == NULL)
	{
		free(flag);
		return (NULL);
	}
	if (*flag == 1)
	{
		free(flag);
		return (ret);
	}
	ret = put_read(fd, ret, stock);
	char *tmp = ret; //for free previous ret if new_ret == NULL
	//ret = NULL;
	if (ret == NULL)
	{
		free(tmp);
		free(flag);
		return (NULL);
	}
	free(flag);
	return (ret);
}
