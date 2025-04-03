/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/03 20:25:35 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static int fd_check;
    int read_count = 0;

    if (fd_check == fd)
    {
        //read the next line
    }
    else
    {
        fd_check = fd;
        //read the first line
    }

    char *buf = (char *)malloc(sizeof(char) * n);
    if (buf == NULL)
        return NULL;
    
    while (*buf != '\n')
    {
        read(fd, buf, 1);
        read_count++;
    }

    
    return buf;
}

int main(void)
{
    ft_putstr_fd("aaaaa\nbbbb\nccc", 4);
    
}