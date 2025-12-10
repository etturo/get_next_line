/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturini <eturini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:32:58 by eturini           #+#    #+#             */
/*   Updated: 2025/12/10 18:59:50 by eturini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *buffer;
	char		*temp_buf;
	size_t		i;

	i = BUFFER_SIZE;
	buffer = (char *)ft_calloc(1, i + 1);
	while (find_newline(buffer, i) == FALSE && i > 0 && read(fd, buffer + (i - BUFFER_SIZE), BUFFER_SIZE) != -1)
	{
		i += BUFFER_SIZE;
		temp_buf = buffer;
		buffer = (char *)ft_calloc(1, i);
		ft_memmove(buffer, temp_buf, i);
		free(temp_buf);
	}
	if (!temp_buf)
		free(temp_buf);
	temp_buf = buffer;
	buffer += find_newline(temp_buf, i);
	printf("\nbuffer: %s\n",buffer);
	return (format_string(temp_buf));
}

#include <fcntl.h>

int main(){
	int fd;

	if ((fd = open("text.txt", O_RDONLY)) == -1)
		return -1;
	printf(">%s<\n", get_next_line(fd));
	printf(">%s<\n", get_next_line(fd));
	printf(">%s<\n", get_next_line(fd));
}