/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturini <eturini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:32:58 by eturini           #+#    #+#             */
/*   Updated: 2025/12/09 18:54:47 by eturini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];

	if (BUFFER_SIZE <= 0 || read(fd, buffer, BUFFER_SIZE) != -1)
		return (NULL);
	return (buffer);
}

#include <fcntl.h>

int main(){
	int fd;

	if ((fd = open("text.txt", O_RDONLY | O_CREAT)) == -1)
		return -1;
	printf("%s \n", get_next_line(fd));
}