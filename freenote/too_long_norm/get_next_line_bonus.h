/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:50:56 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/23 18:09:14 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
#define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct list
{
    int err_flag;
    int fd_check;
    char *stock;
    struct list *next;
} stock_list;

char *get_next_line(int fd);
char *put_stock_bonus(int fd, stock_list *list);
char	*read_put(int fd, char *mem, stock_list *list);
ssize_t	read_buf(int fd, char *buf, char **mem_p, size_t *mem_size);
int	put_buf(char **mem_p, char *buf, stock_list *list, ssize_t read_size);

size_t	ft_strlen(const char *str);
void	*ft_memset(void *mem, int c, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
ssize_t	find_char(const char *str, int c);
char	*alloc_cpy(char *mem, size_t size);

#endif