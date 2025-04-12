/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:30:34 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/12 20:18:22 by rnomoto          ###   ########.fr       */
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
char	*put_stock(int fd, char *stock, char *ret);
char	*read_put(int fd, char *ret, char *stock);
ssize_t	read_buf(int fd, char *buf, char **ret_p, size_t *ret_size);
int		put_buf(char **ret_p, char *buf, char *stock, ssize_t read_size);

size_t	ft_strlen(const char *str);
ssize_t	find_char(const char *str, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_memset(void *mem, int c, size_t n);
char	*strdup_double(char *mem, size_t *old_size);

#endif
