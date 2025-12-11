/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturini <eturini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:32:58 by eturini           #+#    #+#             */
/*   Updated: 2025/12/11 15:43:53 by eturini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char *buffer;
	char		*temp_buf;
	size_t		i;
	size_t		offset;

	buffer = setup_new_buffer(buffer, &offset, fd);
	i = BUFFER_SIZE + offset;
	printf("offset: %ld\nbuffer: %s\n", offset, buffer);
	while (find_newline(buffer, i) != -1 && (read(fd, (buffer + (i + offset)), BUFFER_SIZE) > 0) && BUFFER_SIZE > 0)
	{
		i += BUFFER_SIZE;
		temp_buf = buffer;
		buffer = (char *)ft_calloc(i, sizeof(char));
		ft_memmove(buffer, temp_buf, i - BUFFER_SIZE);
		free(temp_buf);
	}
	temp_buf = format_string(buffer);
	if (!temp_buf)
		free(temp_buf);
	buffer = setup_next_line(buffer);
	return (temp_buf);
}

char	*setup_new_buffer(char *buffer, size_t *offset, int fd)
{
	char	*new_buf;

	if (!buffer)
	{
		*offset = 0;
		read(fd, (buffer), BUFFER_SIZE);
		buffer = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!buffer)
			return NULL;
		//printf("offset: %ld\n", *offset);
		return (buffer);
	}
	*offset = BUFFER_SIZE - find_newline(buffer, BUFFER_SIZE);
	if (*offset == BUFFER_SIZE)
		return buffer;
	new_buf = (char *)ft_calloc(BUFFER_SIZE + *offset, sizeof(char));
	if (!buffer)
		return NULL;
	free(buffer);
	return (new_buf);
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