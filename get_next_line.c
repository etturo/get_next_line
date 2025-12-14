/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturini <eturini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:43:33 by eturini           #+#    #+#             */
/*   Updated: 2025/12/14 18:02:47 by eturini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <=0)
		return NULL;
	line = read_new_line(fd, &stash);
	return line;
}

char	*read_new_line(int fd, char **stash)
{
	char	*buffer;
	long	red_bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	red_bytes = 1;
	while (find_nl(*stash) == -1 && red_bytes != 0)
	{
		red_bytes = read(fd, buffer, BUFFER_SIZE);
		if (red_bytes == - 1)
			return free_for_all(&buffer);
		if (red_bytes == 0)
			break ;
		buffer[red_bytes] = '\0';
		*stash = ft_strjoin(*stash, buffer);
	}
	free(buffer);
	return (get_line(stash));
}


char	*get_line(char **stash)
{
	char	*buffer;
	long	nl_len;
	long	i;
	
	if (!(*stash) || !(*stash)[0])
		return free_for_all(stash);
	nl_len = find_nl(*stash);
	if (nl_len == -1)
	{
		nl_len = 0;
		while ((*stash)[nl_len])
			nl_len++;
	}
	buffer = (char *)malloc(sizeof(char) * (nl_len + 2));
	if (!buffer)
		return free_for_all(stash);
	i = -1;
	while (++i < nl_len)
		buffer[i] = (*stash)[i];
	if (find_nl(*stash) != -1)
		buffer[i++] = '\n';
	buffer[i] = '\0';
	set_next_stash(stash);
	return buffer;
}

char	*set_next_stash(char **stash)
{
	char	*next_stash;
	long	len;
	long	i;
	
	len = 0;
	while ((*stash)[len] && (*stash)[len] != '\n')
		len++;
	if (!(*stash)[len])
		return free_for_all(stash);
	i = 0;
	while ((*stash)[len + i + 1])
		i++;
	next_stash = (char *)malloc(sizeof(char) * (i + 1));
	if (!next_stash)
		return NULL;
	i = 0;
	len++;
	while ((*stash)[len])
		next_stash[i++] = (*stash)[len++];
	next_stash[i] = '\0';
	free(*stash);
	*stash = next_stash;
	return NULL;
}

/* #include <fcntl.h>

int main(){
	int fd;
	char *line;

	if ((fd = open("files/41_no_nl", O_RDONLY)) == -1)
		return -1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("\n=================================\n");
		printf(">%s<", line);
		free(line);
	}
	printf("\n");
}
 */