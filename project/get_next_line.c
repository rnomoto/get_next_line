/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnomoto <rnomoto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:28:08 by rnomoto           #+#    #+#             */
/*   Updated: 2025/04/10 22:10:51 by rnomoto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //for debugging

char	*get_next_line(int fd)
{
	static char	stock[BUFFER_SIZE + 1];
	char		*ret;

	ret = NULL;
	ret = put_store(fd, ret, stock);
	if (ret == NULL)
		return (NULL);
	if (ft_strlen(ret) != ft_strlen(stock))
		return (ret);
	ret = find_enter(fd, ret, stock);
	if (ret == NULL)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
