/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:49:20 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/23 21:38:23 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_c(int fd)
{
	static t_list	*list = NULL;
	t_list			*cur;
	char			c;

	cur = list;
	while (cur != NULL && cur->fd_check != fd)
		cur = cur->next;
	if (cur == NULL)
	{
		cur = (t_list *)malloc(sizeof(t_list)); // null ok
		if (cur == NULL)
			return (-2);
		cur->fd_check = fd;
		cur->buf_p = cur->buf;
		cur->read_size = 0;
		cur->next = list;
		list = cur;
	}
	if (cur->read_size == 0)
	{
		cur->read_size = read(fd, cur->buf, BUFFER_SIZE); //-1 ok
		if (cur->read_size == -1)
		{
			free_list(&list, fd);
			return (-2);
		}
		cur->buf_p = cur->buf;
	}
	cur->read_size--;
	if (cur->read_size < 0)
	{
		free_list(&list, fd);
		return (EOF);
	}
	c = *cur->buf_p++;
	if (c == '\n' && cur->read_size == 0)
		free_list(&list, fd);
	return (c);
}

int	put_c(char **mem_p, size_t *mem_size, char c)
{
	if (*mem_p == NULL)
	{
		*mem_p = alloc_cpy(NULL, BUFFER_SIZE + 1);
		if (*mem_p == NULL)
			return (-1);
		*mem_size = BUFFER_SIZE + 1;
	}
	if (ft_strlen(*mem_p) + 1 >= *mem_size)
	{
		*mem_p = alloc_cpy(*mem_p, *mem_size * 2);
		if (*mem_p == NULL)
			return (-1);
		*mem_size *= 2;
	}
	(*mem_p)[ft_strlen(*mem_p)] = c;
	return (0);
}

char *get_put(int fd, t_list **list)
{
    char c;
    int put_check;
    char *mem;
    size_t mem_size;
    
    mem = NULL;
    mem_size = 0;
    while (1)
    {
        c = get_c(fd);
        if (c == -2)
        {
            free(mem);
            return NULL;
        }
        else if (c == EOF)
        {
            free_list(list, fd);
            break;
        }
        put_check = put_c(&mem, &mem_size, c);
        if (put_check == -1)
            return NULL;
        else if (c == '\n')
            break;
    }
    return mem;
}

char	*get_next_line(int fd)
{
	char	*mem;
    static t_list *list = NULL;

	mem = get_put(fd, &list);
	if (mem == NULL)
		return (NULL);
	mem = alloc_cpy(mem, ft_strlen(mem) + 1);
	if (mem == NULL)
		return (NULL);
	return (mem);
}
