/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:00:44 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/18 16:59:29 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char *put_stock_bonus(int fd, stock_list *list)
{
	char *cp;
	char *mem;
	ssize_t nl_pos;

	printf("stock1: \"%s\"\n", list->stock);
	cp = (char *)malloc(sizeof(char) * ft_strlen(list->stock) + 1);
	if (cp == NULL)
		return NULL;
	ft_strlcpy(cp, list->stock, ft_strlen(list->stock) + 1);
	mem = alloc_cpy(NULL, ft_strlen(list->stock) + 1);
	if (mem == NULL)
		return (free(cp), NULL);
	nl_pos = find_char(list->stock, '\n');
	//printf("stock: \"%s\"\n", list->stock);
	printf("nl_pos: %zd\n", nl_pos);
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

	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size == 0 && (buf[0] != '\0' || *mem_p[0] != '\0'))
		return (0);
	else if (read_size <= 0)
		return (-1);
	if ((ft_strlen(*mem_p) + (size_t)read_size + 1) > *mem_size)
	{
		tmp = *mem_p;
		new_size = (*mem_size * 2) + BUFFER_SIZE;
		*mem_p = (char *)malloc(sizeof(char) * new_size);
		if (*mem_p == NULL)
			return (-1);
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
		printf("stock2: \"%s\"\n", list->stock);
	}
	return (0);
}

char	*read_put(int fd, char *mem, stock_list *list)
{
	char	*buf;
	ssize_t	read_size;
	size_t	mem_size;
	int		put_check;

	//printf("stock1: \"%s\"\n", list->stock);
	buf = alloc_cpy(NULL, BUFFER_SIZE + 1);
	if (buf == NULL)
		return (free(mem), NULL);
	mem_size = ft_strlen(list->stock) + 1;
	while (1)
	{
		read_size = read_buf(fd, buf, &mem, &mem_size);
		put_check = put_buf(&mem, buf, list, read_size);
		if (put_check <= 0)
			break ;
	}
	if (read_size == 0 || put_check == 0)
	{
		if (buf[0] == '\0')
			ft_memset(list->stock, '\0', (BUFFER_SIZE + 1));
		return (free(buf), mem);
	}
	list->err_flag = 1;
	return (free(mem), free(buf), NULL);
}

int	ft_lstsize(stock_list *lst)
{
	int	count;

	count = 1;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

char *get_next_line(int fd)
{
    static stock_list *list = NULL;
	stock_list *cur = list;
    char *mem;
    char *ret;

	printf("size: %d\n", ft_lstsize(list));
	while (list != NULL)
	{
		if (cur->fd_check == fd)
			break;
		printf("      fd: %d\n", fd);
		printf("fd_check: %d\n", cur->fd_check);
		cur = cur->next;
	}
	if (cur == NULL)
	{
		cur = (stock_list *)malloc(sizeof(list));
		if (cur == NULL)
			return (NULL);
		cur->fd_check = fd;
		cur->err_flag = 0;
		cur->stock = alloc_cpy(NULL, BUFFER_SIZE + 1);
		if (cur->stock == NULL)
			return NULL;
	}
    mem = put_stock_bonus(fd, cur);
	if (mem == NULL)
		return NULL;
	if (find_char(mem, '\n') == -1)
	{
		printf("read step in\n");
		//printf("%s\n", list->stock);
		//printf("step in.\n");
		mem = read_put(fd, mem, cur);
		if (mem == NULL)
			return (NULL);
	}
	ret = alloc_cpy(mem, ft_strlen(mem) + 1);
	if (ret == NULL)
		return (NULL);
	//list = head;
	return (ret);
}