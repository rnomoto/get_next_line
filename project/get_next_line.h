/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:30:34 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/18 13:47:31 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*put_stock(int fd, char *stock, int *fd_check);
char	*read_put(int fd, char *mem, char *stock, int *err_flag);
ssize_t	read_buf(int fd, char *buf, char **mem_p, size_t *mem_size);
int		put_buf(char **mem_p, char *buf, char *stock, ssize_t read_size);

size_t	ft_strlen(const char *str);
ssize_t	find_char(const char *str, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_memset(void *mem, int c, size_t n);
char	*alloc_cpy(char *mem, size_t size);

#endif
