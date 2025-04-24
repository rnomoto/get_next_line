/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:49:20 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/23 18:07:35 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*put_stock(int fd, char *stock, int *fd_check)
{
	ssize_t	nl_pos;
	char	*cp;
	char	*mem;

	cp = (char *)malloc(sizeof(char) * ft_strlen(stock) + 1); //null ok
	if (cp == NULL)
		return (NULL);
	ft_strlcpy(cp, stock, ft_strlen(stock) + 1);
	mem = alloc_cpy(NULL, ft_strlen(stock) + 1);
	if (mem == NULL)
	{
		free(cp);
		return (NULL);
	}
	nl_pos = find_char(stock, '\n');
	if (nl_pos != -1)
	{
		ft_strlcpy(mem, cp, (nl_pos + 1) + 1);
		ft_strlcpy(stock, (cp + nl_pos + 1), ft_strlen(cp + nl_pos + 1) + 1);
	}
	else
		ft_strlcpy(mem, cp, ft_strlen(cp) + 1);
	*fd_check = fd;
	free(cp);
	return (mem);
}

ssize_t	read_buf(int fd, char *buf, char **mem_p, size_t *mem_size)
{
	ssize_t	read_size;
	size_t	new_size;
	char	*tmp;

	read_size = read(fd, buf, BUFFER_SIZE); //-1 ok
	if (read_size == 0 && (buf[0] != '\0' || *mem_p[0] != '\0'))
		return (0);
	else if (read_size <= 0)
		return (-1);
	if ((ft_strlen(*mem_p) + (size_t)read_size + 1) > *mem_size)
	{
		tmp = *mem_p;
		new_size = (*mem_size * 2) + BUFFER_SIZE;
		*mem_p = (char *)malloc(sizeof(char) * new_size); //null ok
		if (*mem_p == NULL)
			return (free(tmp), -1);
		*mem_size = new_size;
		ft_memset(*mem_p, '\0', *mem_size);
		ft_strlcpy(*mem_p, tmp, ft_strlen(tmp) + 1);
		free(tmp);
	}
	return (read_size);
}

int	put_buf(char **mem_p, char *buf, char *stock, ssize_t read_size)
{
	ssize_t	nl_pos;

	if (read_size == -1)
		return (-1);
	ft_memset(stock, '\0', BUFFER_SIZE + 1);
	nl_pos = find_char(buf, '\n');
	if (nl_pos == -1 && read_size == BUFFER_SIZE)
	{
		ft_strlcpy(*mem_p + ft_strlen(*mem_p), buf, read_size + 1);
		return (1);
	}
	else if (nl_pos == -1)
		ft_strlcpy(*mem_p + ft_strlen(*mem_p), buf, (read_size + 1));
	else
	{
		ft_strlcpy(*mem_p + ft_strlen(*mem_p), buf, (nl_pos + 1) + 1);
		ft_strlcpy(stock, buf + nl_pos + 1, read_size - nl_pos);
	}
	return (0);
}

char	*read_put(int fd, char *mem, char *stock, int *err_flag)
{
	char	*buf;
	ssize_t	read_size;
	size_t	mem_size;
	int		put_check;

	buf = alloc_cpy(NULL, BUFFER_SIZE + 1); //null ok
	if (buf == NULL)
		return (free(mem), NULL);
	mem_size = ft_strlen(stock) + 1;
	while (1)
	{
		read_size = read_buf(fd, buf, &mem, &mem_size); //-1 ok
		put_check = put_buf(&mem, buf, stock, read_size); //-1 ok
		if (put_check <= 0)
			break ;
	}
	if (read_size == 0 || put_check == 0)
	{
		if (buf[0] == '\0')
			ft_memset(stock, '\0', (BUFFER_SIZE + 1));
		return (free(buf), mem);
	}
	*err_flag = 1;
	return (free(mem), free(buf), NULL);
}

char	*get_next_line(int fd)
{
	static char	stock[BUFFER_SIZE + 1];
	static int	fd_check = -2;
	static int	err_flag = 0;
	char		*mem;
	char		*ret;

	if ((fd != fd_check || fd_check == -2) || err_flag == 1)
	{
		ft_memset(stock, '\0', BUFFER_SIZE + 1);
		fd_check = -2;
		err_flag = 0;
	}
	mem = put_stock(fd, stock, &fd_check); //null ok
	if (mem == NULL)
		return (NULL);
	else if (find_char(mem, '\n') == -1)
	{
		mem = read_put(fd, mem, stock, &err_flag);
		if (mem == NULL)
			return (NULL);
	}
	ret = alloc_cpy(mem, ft_strlen(mem) + 1); //null ok
	if (ret == NULL)
		return NULL;
	return (ret);
}