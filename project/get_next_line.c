/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/13 11:29:52 by rnomoto          ###   ########.fr       */
=======
/*   Updated: 2025/04/13 11:37:59 by rnomoto          ###   ########.fr       */
>>>>>>> 690434c (leaks)
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //for debug

char	*put_stock(int fd, char *stock, char *ret)
{
	static int	fd_check = -2; //is it ok to define -2 to fd_check?
	ssize_t		enter_pos;
	char		*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(stock) + 1)); // null ok
	//tmp = NULL;
	if (tmp == NULL)
		return (NULL);
	//printf("fd: %d\n",fd);
	if (fd == fd_check && fd_check != -2)
	{
		// printf("stock: \"%s\"\n", stock);
		ft_strlcpy(tmp, stock, (ft_strlen(stock) + 1));
		// printf("tmp: \"%s\"\n", tmp);
		enter_pos = find_char(stock, '\n');
		// printf("enter_pos: %zd\n", enter_pos);
		if (enter_pos != -1)
		{
			ft_strlcpy(ret, tmp, (enter_pos + 2));
			// printf("ret: \"%s\"", ret);
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

	//char *tmp_free;
	read_size = read(fd, buf, BUFFER_SIZE);
	//printf("read_size: %zd\n", read_size);
	if (read_size == 0 && buf[0] != '\0')
		return (0);
	else if (read_size <= 0)
		return (-1);
	if ((ft_strlen(*ret_p) + (size_t)read_size + 1) > *ret_size)
	{
		//tmp_free = *ret_p;
		*ret_p = strdup_double(*ret_p, ret_size); // null ok. maybe tmp_free is not necessary
		//*ret_p = NULL;
		//free(tmp_free);
		if (*ret_p == NULL)
		{
			return (-1);
		}
	}
	return (read_size);
}

int	put_buf(char **ret_p, char *buf, char *stock, ssize_t read_size)
{
	ssize_t	enter_pos;

	enter_pos = find_char(buf, '\n');
	//printf("buf: \"%s\"\n", buf);
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
			//printf("ret: \"%s\"\n", *ret_p);
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
	//char *tmp;

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
	*ret_size = ft_strlen(stock) + 1;
	ft_memset(buf, '\0', (BUFFER_SIZE + 1));
	//tmp = *ret_p;
	while (1)
	{
		read_size = read_buf(fd, buf, ret_p, ret_size);
		put_check = put_buf(ret_p, buf, stock, read_size);
		if (put_check <= 0)
			break ;
	}
	//if (*ret_p != tmp)
		//free(tmp);
	free(buf);
	free(ret_size);
	if (read_size == 0 || put_check == 0)
		return (ret);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	stock[BUFFER_SIZE];
	char		*ret;
	char		*tmp;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(stock) + 1));
	//ret = NULL;
	if (ret == NULL)
		return (NULL);
	ft_memset(ret, '\0', (ft_strlen(stock) + 1));
	tmp = ret;
	ret = put_stock(fd, stock, ret);
	//ret = NULL;
	if (ret == NULL)
	{
		free(tmp);
		return (NULL);
	}
	if (find_char(ret, '\n') != -1)
	{
		//free(tmp);
		return ret;
	}
	// if (ret != tmp)
    // 	free(tmp);
	tmp = ret; // for free previous ret if new_ret == NULL
	ret = read_put(fd, ret, stock); // null ok
	//ret = NULL;
	if (ret == NULL)
	{
<<<<<<< HEAD
        free(tmp);
=======
		free(tmp);
>>>>>>> 690434c (leaks)
		return (NULL);
	}
	free(tmp);
	return (ret);
}
