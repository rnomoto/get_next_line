/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/12 20:48:49 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //for debug

char	*put_stock(int fd, char *stock, char *ret)
{
	static int	fd_check = -2;
	ssize_t		enter_pos;
	char		*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(stock) + 1)); // null ok
	if (tmp == NULL)
		return (NULL);
	if (fd == fd_check)
	{
		printf("stock: \"%s\"\n", stock);
		ft_strlcpy(tmp, stock, (ft_strlen(stock) + 1));
		enter_pos = find_char(stock, '\n');
		if (enter_pos != -1)
		{
			ft_strlcpy(ret, tmp, (enter_pos + 2));
			ft_strlcpy(stock, (tmp + enter_pos + 1), ft_strlen(tmp + enter_pos + 1) + 1);
			free(tmp);
			return (ret);
		}
		ft_strlcpy(ret, tmp, (ft_strlen(stock) + 1));
	}
	ft_memset(stock, '\0', ft_strlen(stock) + 1);
	fd_check = fd;
	free(tmp);
	return (ret);
}

ssize_t	read_buf(int fd, char *buf, char **ret_p, size_t *ret_size)
{
	ssize_t	read_size;

	// char *tmp_free;
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size == 0 && buf[0] != '\0')
		return (0);
	else if (read_size <= 0)
		return (-1);
	if ((ft_strlen(*ret_p) + (size_t)read_size + 1) > *ret_size)
	{
		// tmp_free = *ret_p;
		*ret_p = strdup_double(*ret_p, ret_size); // null ok. maybe tmp_free is not necessary
		//*ret_p = NULL;
		if (*ret_p == NULL)
		{
			// free(tmp_free);
			return (-1);
		}
	}
	return (read_size);
}

int	put_buf(char **ret_p, char *buf, char *stock, ssize_t read_size)
{
	ssize_t	enter_pos;

	enter_pos = find_char(buf, '\n');
	printf("buf: \"%s\"\n", buf);
	if (read_size == -1)
		return (-1);
	if (enter_pos == -1 && read_size == BUFFER_SIZE)
		ft_strlcpy((*ret_p + ft_strlen(*ret_p)), buf, (read_size + 1)); //+1?
	else
	{
		if (enter_pos == -1)
			ft_strlcpy((*ret_p + ft_strlen(*ret_p)), buf, (read_size + 1)); //+1?
		else
		{
			ft_strlcpy((*ret_p + ft_strlen(*ret_p)), buf, (enter_pos + 2));
			printf("ret: \"%s\"\n", *ret_p);
			//if (read_size == BUFFER_SIZE)
			ft_strlcpy(stock, (buf + enter_pos + 1), (read_size - enter_pos));
		}
		return (0);
	}
	return (1);
}

char	*read_put(int fd, char *ret, char *stock)
{
	char	*buf;
	ssize_t	read_size;
	size_t	*ret_size;
	int		put_check;
	char	**ret_p;

	ret_p = &ret;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); // null ok
	if (buf == NULL)
		return (NULL);
	ret_size = (size_t *)malloc(sizeof(size_t)); // null ok
	if (ret_size == NULL)
	{
		free(buf);
		return (NULL);
	}
	*ret_size = BUFFER_SIZE + 1;
	ft_memset(buf, '\0', (BUFFER_SIZE + 1));
	while (1)
	{
		read_size = read_buf(fd, buf, ret_p, ret_size);
		put_check = put_buf(ret_p, buf, stock, read_size);
		if (put_check <= 0)
			break ;
	}
	free(buf);
	free(ret_size);
	if (read_size == 0 || put_check == 0)
		return (ret);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	stock[BUFFER_SIZE + 1];
	char		*ret;
	char		*tmp;

	ret = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); // null ok
	if (ret == NULL)
		return (NULL);
	ft_memset(ret, '\0', (BUFFER_SIZE + 1));
	tmp = ret;
	ret = put_stock(fd, stock, ret); // null ok
	if (ret == NULL)
	{
		free(tmp);
		return (NULL);
	}
	tmp = ret;                      // for free previous ret if new_ret == NULL
	ret = read_put(fd, ret, stock); // null ok
	if (ret == NULL)
	{
		free(tmp);
		return (NULL);
	}
	return (ret);
}
