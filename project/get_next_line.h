/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:30:34 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/10 22:11:10 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>

char	*get_next_line(int fd);
ssize_t	ft_strlen(const char *str);
char	*add_allocate(char *mem, size_t old_size);
char	*put_store(int fd, char *ret, char *stock);
char *find_enter(int fd, char *ret, char *stock);
int put_buf(char *ret, char *stock, char *read_buf, ssize_t read_size);

#endif
