/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:52:59 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/10 22:11:00 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

ssize_t	ft_strlen(const char *str)
{
	ssize_t	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*add_allocate(char *mem, size_t old_size)
{
	char	*new_mem;
	size_t	i;

	i = 0;
	new_mem = (char *)malloc(sizeof(char) * (old_size + BUFFER_SIZE + 1));
	if (new_mem == NULL)
		return (NULL);
	while (i < (old_size + BUFFER_SIZE) + 1)
	{
		if (mem != NULL && i < old_size)
			new_mem[i] = mem[i];
		else
			new_mem[i] = '\0';
		i++;
	}
	if (mem != NULL)
		free(mem);
	return (new_mem);
}

char	*put_store(int fd, char *ret, char *stock)
{
	static int	fd_check = -2;
	ssize_t		i;
	ssize_t		j;

	i = 0;
	j = 0;
	ret = add_allocate(ret, 0);
	if (ret == NULL)
		return (NULL);
	while ((fd == fd_check) && (i < ft_strlen(stock)))
	{
		ret[i] = stock[i];
		if (ret[i] == '\n')
			break ;
		i++;
	}
	while ((fd == fd_check) && ((i + j) < ft_strlen(stock)))
	{
		stock[j] = stock[i + j];
		j++;
	}
	fd_check = fd;
	return (ret);
}

int	put_buf(char *ret, char *stock, char *read_buf, ssize_t read_size)
{
	ssize_t	i;
	ssize_t	j;
	int		flag;

	i = 0;
	j = 0;
	flag = 1;
    //printf("hey\n");
	while (ret[i] != '\0')
		i++;
	while (j < read_size)
	{
		ret[i] = read_buf[j];
        //printf("debug: %c", read_buf[j]);
		j++;
		if (ret[i] == '\n' || ret[i] == '\0')
		{
			flag = 0;
			break ;
		}
		i++;
	}
	i = 0;
	while (i + j < read_size)
	{
		stock[i] = read_buf[i + j];
		i++;
	}
	if (i + j == read_size)
		stock[i] = '\0';
	return (flag);
}

char	*find_enter(int fd, char *ret, char *stock)
{
	char	*read_buf;
	ssize_t	read_size;
	size_t	count;

	count = 1;
	read_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_buf == NULL)
		return (NULL);
	read_buf[BUFFER_SIZE] = '\0';
	while (1)
	{
		read_size = read(fd, read_buf, BUFFER_SIZE);
		ret = add_allocate(ret, BUFFER_SIZE * count);
        //printf("debug: %zd\n", read_size);
		if (read_size <= 0 || ret == NULL)
		{
			free(read_buf);
			if (ret)
				free(ret);
			return (NULL);
		}
		if (put_buf(ret, stock, read_buf, read_size) == 0)
			break ;
		count++;
	}
	free(read_buf);
	return (ret);
}
