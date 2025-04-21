/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:00:44 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/21 17:37:41 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h> //debug

char *put_stock_bonus(int fd, stock_list *list)
{
	char *cp;
	char *mem;
	ssize_t nl_pos;

	cp = (char *)malloc(sizeof(char) * ft_strlen(list->stock) + 1); //null ok
	if (cp == NULL)
		return NULL;
	ft_strlcpy(cp, list->stock, ft_strlen(list->stock) + 1);
	mem = alloc_cpy(NULL, ft_strlen(list->stock) + 1); //null ok
	if (mem == NULL)
		return (free(cp), NULL);
	nl_pos = find_char(list->stock, '\n');
	if (nl_pos != -1)
	{
		ft_strlcpy(mem, cp, (nl_pos + 1) + 1);
		ft_strlcpy(list->stock, (cp + nl_pos + 1), ft_strlen(cp + nl_pos + 1) + 1);
	}
	else
		ft_strlcpy(mem, cp, ft_strlen(cp) + 1);
	list->fd_check = fd;
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

int	put_buf(char **mem_p, char *buf, stock_list *list, ssize_t read_size)
{
	ssize_t	nl_pos;

	if (read_size == -1)
		return (-1);
	ft_memset(list->stock, '\0', BUFFER_SIZE + 1);
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
		ft_strlcpy(list->stock, buf + nl_pos + 1, read_size - nl_pos);
	}
	return (0);
}

char	*read_put(int fd, char *mem, stock_list *list)
{
	char	*buf;
	ssize_t	read_size;
	size_t	mem_size;
	int		put_check;

	buf = alloc_cpy(NULL, BUFFER_SIZE + 1); //null ok
	if (buf == NULL)
		return (free(mem), NULL);
	mem_size = ft_strlen(list->stock) + 1;
	while (1)
	{
		read_size = read_buf(fd, buf, &mem, &mem_size); //-1 ok
		put_check = put_buf(&mem, buf, list, read_size); //-1 ok
		if (put_check <= 0)
			break ;
	}
	if (read_size == 0 || put_check == 0)
	{
		if (buf[0] == '\0')
		{
			ft_memset(list->stock, '\0', (BUFFER_SIZE + 1));
			// free(list->stock);
			// free(list);
		}
		return (free(buf), mem);
	}
	list->err_flag = 1;
	return (free(mem), free(buf), NULL);
}

char *get_next_line(int fd)
{
    static stock_list *list = NULL;
	stock_list *cur = list;
    char *mem;
    char *ret;
	int is_new = 0;

	while (cur != NULL && cur->fd_check != fd)
		cur = cur->next;
	if (cur == NULL)
	{
		cur = (stock_list *)malloc(sizeof(stock_list)); //null ok
		if (cur == NULL)
			return (NULL);
		is_new = 1;
		cur->fd_check = fd;
		cur->err_flag = 0;
		cur->stock = alloc_cpy(NULL, BUFFER_SIZE + 1); //null ok
		if (cur->stock == NULL)
			return (free(cur), NULL);
		cur->next = list;
		list = cur;
	}
    mem = put_stock_bonus(fd, cur); //null ok
	if (mem == NULL)
		return NULL;
	if (find_char(mem, '\n') == -1)
	{
		mem = read_put(fd, mem, cur); //should define tmp to free
		if (mem == NULL)
			return NULL;
	}
	ret = alloc_cpy(mem, ft_strlen(mem) + 1); //null ok
	if (ret == NULL)
		return NULL;
	return (ret);
}

//err_flag ??