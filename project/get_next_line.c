/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/05 19:50:16 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd)
{
    static char buf[BUFSIZ];
    int i = 0;
    int tmp;
    
    char *output = (char *)ft_calloc(sizeof buf,sizeof(char));
    if (output == NULL)
        return NULL;
    while(1)
    {
        tmp = ft_getc(fd);
        if (tmp == EOF || tmp == '\n')
            break;
        output[i] = tmp;
        i++;
    }
    return output;
}
