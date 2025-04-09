/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:30:34 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/09 13:52:31 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 10

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	*ft_calloc(size_t nmemb, size_t size);
char	*double_buffer(char *old_buf, size_t size);
char	*put_line(char *buf, size_t size, int fd);
int		read_c(int fd);
void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *str, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t size);

#endif