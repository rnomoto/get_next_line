/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:49:20 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/24 13:15:01 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*find_cur(int fd, t_list **list)
{
	t_list	*cur;

	cur = *list;
	while (cur != NULL && cur->fd_check != fd)
		cur = cur->next;
	if (cur == NULL)
	{
		cur = (t_list *)malloc(sizeof(t_list));
		if (cur == NULL)
			return (NULL);
		cur->fd_check = fd;
		cur->buf_p = cur->buf;
		cur->read_size = 0;
		cur->next = *list;
		*list = cur;
	}
	return (cur);
}

int	get_c(int fd, t_list **list)
{
	t_list	*cur;
	char	c;

	cur = find_cur(fd, list);
	if (cur == NULL)
		return (-2);
	if (cur->read_size == 0)
	{
		cur->read_size = read(fd, cur->buf, BUFFER_SIZE);
		if (cur->read_size == -1)
		{
			free_list(list, fd);
			return (-2);
		}
		cur->buf_p = cur->buf;
	}
	cur->read_size--;
	if (cur->read_size < 0)
	{
		free_list(list, fd);
		return (EOF);
	}
	c = *cur->buf_p++;
	if (cur->read_size <= 0 && fd == 0)
		free_list(list, fd);
	return (c);
}

int	put_c(t_mem *m_list, char c, t_list **list, int fd)
{
	if (m_list->mem == NULL)
	{
		m_list->mem = alloc_cpy(NULL, BUFFER_SIZE + 1, list, fd);
		if (m_list->mem == NULL)
			return (-1);
		m_list->size = BUFFER_SIZE + 1;
	}
	if (ft_strlen(m_list->mem) + 1 >= m_list->size)
	{
		m_list->mem = alloc_cpy(m_list->mem, m_list->size * 2, list, fd);
		if (m_list->mem == NULL)
			return (-1);
		m_list->size *= 2;
	}
	(m_list->mem)[ft_strlen(m_list->mem)] = c;
	return (0);
}

char	*get_put(int fd, t_list **list)
{
	char	c;
	int		put_check;
	t_mem	m_list;

	m_list.mem = NULL;
	m_list.size = 0;
	while (1)
	{
		c = get_c(fd, list);
		if (c == -2)
		{
			free(m_list.mem);
			return (NULL);
		}
		else if (c == EOF)
			break ;
		put_check = put_c(&m_list, c, list, fd);
		if (put_check == -1)
			return (NULL);
		else if (c == '\n')
			break ;
	}
	return (m_list.mem);
}

char	*get_next_line(int fd)
{
	char			*mem;
	static t_list	*list = NULL;

	mem = get_put(fd, &list);
	if (mem == NULL)
		return (NULL);
	mem = alloc_cpy(mem, ft_strlen(mem) + 1, &list, fd);
	if (mem == NULL)
		return (NULL);
	return (mem);
}
