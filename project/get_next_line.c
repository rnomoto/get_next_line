/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:49:20 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/16 15:03:00 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //for debug

char	*put_stock(int fd, char *stock, char *mem, int *err_flag)
{
	static int	fd_check = -2; //is it ok to define -2 to fd_check?
	ssize_t		nl_pos;
	char *cp;

	if (*err_flag == 1)
	{
		ft_memset(stock, '\0', BUFFER_SIZE + 1);
		fd_check = -2;
		*err_flag = 0;
	}
	//printf("stock: \"%s\"\n", stock);
	if (fd != fd_check || fd_check == -2)
		ft_memset(stock, '\0', BUFFER_SIZE + 1);
	cp = (char *)malloc(sizeof(char) * ft_strlen(stock) + 1);
	//ret = NULL
	if (cp == NULL)
		return NULL;
	ft_strlcpy(cp, stock, ft_strlen(stock) + 1);
	//printf("cp: \"%s\"\n", cp);
	mem = (char *)malloc(sizeof(char) * (ft_strlen(stock) + 1));
	//ret = NULL;
	if (mem == NULL)
	{
		free(cp);
		return NULL;
	}
	ft_strlcpy(mem, stock, ft_strlen(stock) + 1);
	nl_pos = find_char(stock, '\n');
	if (nl_pos != -1)
	{
		ft_strlcpy(mem, cp, (nl_pos + 1) + 1);
		ft_strlcpy(stock, (cp + nl_pos + 1), ft_strlen(cp + nl_pos + 1) + 1);
		free(cp);
		return mem;
	}
	ft_strlcpy(mem, cp, ft_strlen(cp) + 1);
	fd_check = fd;
	free(cp);
	//printf("mem: \"%s\"\n", mem);
	return mem;
}

ssize_t read_buf(int fd, char *buf, char **mem_p, size_t *mem_size)
{
	ssize_t read_size;

	read_size = read(fd, buf, BUFFER_SIZE);
	//printf("read_size: %zd\n", read_size);
	if (read_size == 0 && (buf[0] != '\0' || *mem_p[0] != '\0'))
		return 0;
	else if (read_size <= 0)
		return -1;
	if ((ft_strlen(*mem_p) + (size_t)read_size + 1) > *mem_size)
	{
		*mem_p = strdup_double(*mem_p, mem_size);
		if (*mem_p == NULL)
			return -1;
	}
	return read_size;
}

int put_buf(char **mem_p, char *buf, char *stock, ssize_t read_size)
{
	ssize_t nl_pos;

	if (read_size == -1)
		return -1;
	ft_memset(stock, '\0', BUFFER_SIZE + 1); //initialize stock before putting a read_buf
	nl_pos = find_char(buf, '\n');
	if (nl_pos == -1 && read_size == BUFFER_SIZE)
	{
		ft_strlcpy(*mem_p + ft_strlen(*mem_p), buf, read_size + 1);
		return 1;
	}
	else if (nl_pos == -1)
		ft_strlcpy(*mem_p + ft_strlen(*mem_p), buf, (read_size + 1)); //+1?
	else
	{
		ft_strlcpy(*mem_p + ft_strlen(*mem_p), buf, (nl_pos + 1) + 1);
		ft_strlcpy(stock, buf + nl_pos + 1, read_size - nl_pos);
	}
	return 0;
}

//use tmp??
//use ret_p = &ret?
char *read_put(int fd, char *mem, char *stock, int *err_flag)
{
	char *buf;
	ssize_t read_size;
	size_t mem_size;
	int put_check;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	// buf = NULL;
	if (buf == NULL)
	{
		free(mem);
		return NULL;
	}
	ft_memset(buf, '\0', (BUFFER_SIZE + 1));
	mem_size = ft_strlen(stock) + 1;
	while (1)
	{
		read_size = read_buf(fd, buf, &mem, &mem_size);
		put_check = put_buf(&mem, buf, stock, read_size);
		if (put_check <= 0)
			break ;
	}
	if (read_size == 0 || put_check == 0)
	{
		if (buf[0] =='\0')
			ft_memset(stock, '\0', (BUFFER_SIZE + 1));
		free(buf);
		return (mem);
	}
	*err_flag = 1;
	free(mem);
	free(buf);
	return (NULL);
}

//free later. put inside a helper func
//use tmp?
char *get_next_line(int fd)
{
	static char stock[BUFFER_SIZE + 1];
	//char **ret_p;
	char *mem;
	char *ret;

	static int err_flag = 0;

	//ret_p = &ret;
	mem = NULL;
	mem = put_stock(fd, stock, mem, &err_flag);
	if (mem == NULL)
		return NULL;
	else if (find_char(mem, '\n') != -1)
	{
		ret = (char *)malloc(sizeof(char) * (ft_strlen(mem) + 1));
		if (ret == NULL)
		{
			free(mem);
			return NULL;
		}
		ft_memset(ret, '\0', ft_strlen(mem) + 1);
		ft_strlcpy(ret, mem, ft_strlen(mem) + 1);
		free(mem);
		return ret;
	}
	mem = read_put(fd, mem, stock, &err_flag);
	if (mem == NULL)
		return NULL;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(mem) + 1));
	if (ret == NULL)
	{
		free(mem);
		return NULL;
	}
	ft_memset(ret, '\0', ft_strlen(mem) + 1);
	ft_strlcpy(ret, mem, ft_strlen(mem) + 1);
	free(mem);
	return ret;
}
