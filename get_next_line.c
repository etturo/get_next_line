/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturini <eturini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:32:58 by eturini           #+#    #+#             */
/*   Updated: 2025/12/13 15:38:58 by eturini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_for_all(void *buffer)
{
	if (buffer)
		free(buffer);
	buffer = NULL;
	return NULL;
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*temp_buf;
	long 		offset;
	size_t		i;

	offset = 0;
	if (!setup_new_buffer(&buffer, fd , &offset))
		return free_for_all(buffer);
	i = BUFFER_SIZE + offset;
	temp_buf = NULL;
	while (find_newline(buffer, i) == -1 && BUFFER_SIZE > 0)
	{
		i += BUFFER_SIZE;
		temp_buf = buffer;
		buffer = (char *)ft_calloc(i, sizeof(char));
		if (!buffer)
			return (NULL);
		ft_memmove(buffer, temp_buf, i - BUFFER_SIZE);
		free(temp_buf);
		if (read(fd, buffer + i - BUFFER_SIZE, BUFFER_SIZE) <= 0)
			return free_for_all(buffer);
	}
	return (set_next_buffer(&buffer, i));
}


#include <fcntl.h>

int main(){
	int fd;
	char *line;

	if ((fd = open("text.txt", O_RDONLY)) == -1)
		return -1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("\n=================================\n");
		printf(">%s<", line);
		free(line);
	}
	printf("\n");
}