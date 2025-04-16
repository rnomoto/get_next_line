/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:00:44 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/16 18:57:03 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memset(void *mem, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem_cast;
	unsigned char	c_cast;

	i = 0;
	mem_cast = (unsigned char *)mem;
	c_cast = (unsigned char)c;
	while (i < n)
	{
		mem_cast[i] = c_cast;
		i++;
	}
	return (mem_cast);
}

char *put_stock_bonus(int fd, char *mem, stock_list *list)
{
	char *cp;

	while (list != NULL)
	{
		if (list->fd_check == fd)
			break;
		list = list->next;
	}
	if (list == NULL)
	{
		list->fd_check = fd;
		list->stock = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (list->stock == NULL)
			return NULL;
		ft_memset(list->stock, '\0', BUFFER_SIZE + 1);
	}
	cp = (char *)malloc(sizeof(char) * ft_strlen(list->stock) + 1);
	if (cp == NULL)
		return NULL;
	ft_strlcpy(cp, list->stock, ft_strlen(list->stock) + 1);
	mem = (char *)malloc(sizeof(char))
}

char *get_next_line(int fd)
{
    static stock_list *list = NULL;
    char *mem;
    char *ret;

	mem = NULL;
    mem = put_stock_bonus(fd, mem, list);
	    

}