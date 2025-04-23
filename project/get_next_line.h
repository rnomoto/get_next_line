/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:30:34 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/23 15:45:20 by rnomoto          ###   ########.fr       */
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
# include <stdio.h>

typedef struct s_list
{
    int fd_check;
    char buf[BUFFER_SIZE];
    char *buf_p;
    ssize_t read_size;
    struct s_list *next;
} t_list;

char	*get_next_line(int fd);
int	get_c(int fd);
int put_c(char **mem, size_t *mem_size, char c);

size_t	ft_strlen(const char *str);
void	*ft_memset(void *mem, int c, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*alloc_cpy(char *mem, size_t size);

void free_list(t_list **list, int fd);

#endif
