/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:50:56 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/24 12:19:37 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	int				fd_check;
	char			buf[BUFFER_SIZE];
	char			*buf_p;
	ssize_t			read_size;
	struct s_list	*next;
}					t_list;

typedef struct s_mem
{
	char			*mem;
	size_t			size;
}					t_mem;

char				*get_next_line(int fd);

int					get_c(int fd, t_list **list);
int					put_c(t_mem *m_list, char c, t_list **list, int fd);
char				*get_put(int fd, t_list **list);
t_list				*find_cur(int fd, t_list **list);

size_t				ft_strlen(const char *str);
void				*ft_memset(void *mem, int c, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*alloc_cpy(char *mem, size_t size, t_list **list, int fd);
void				free_list(t_list **list, int fd);

#endif