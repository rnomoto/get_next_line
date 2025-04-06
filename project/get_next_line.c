/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/06 15:17:39 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd)
{
    char *buf;
    char c;
    int i = 0;
    
    c = 'a'; //initiate
    buf = (char *)ft_calloc(sizeof(char), 1000);
    if (buf == NULL)
        return NULL;
    while (c != '\n')
    {
        c = read_c(fd);
        if (c == -1 && i == 0)
            return NULL;
        else if (c == -1)
            break;
        buf[i] = c;
        i++;
    }
    return buf;
}
