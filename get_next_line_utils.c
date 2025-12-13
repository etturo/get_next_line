/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturini <eturini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:33:00 by eturini           #+#    #+#             */
/*   Updated: 2025/12/13 15:37:21 by eturini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;

	if (src > dest)
	{
		s = (char *)src;
		d = (char *)dest;
		while (n--)
			*d++ = *s++;
	}
	else
	{
		s = (char *)src + n;
		d = (char *)dest + n;
		while (n--)
			*--d = *--s;
	}
	return (dest);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*s;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > __SIZE_MAX__ / size)
		return ((void *)0);
	s = (char *)malloc(size * nmemb);
	if (!s)
		return ((void *)0);
	i = 0;
	while (i < (size * nmemb))
		((char *)s)[i++] = 0;
	return (s);
}

long	find_newline(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s[i])
	{
		if (s[i] == '\n')
			return i;
		i++;
	}
	return (-1);
}

// this function takes the buffer and set for the next iteration
// also trim the strign to return reaching the new line
char	*set_next_buffer(char **buffer, size_t len)
{
	char	*format_buff;
	char	*temp_buf;

	temp_buf = *buffer;
	format_buff = (char *)ft_calloc(find_newline(temp_buf, len) + 2, sizeof(char));
	if (!format_buff)
		return NULL;
	ft_memmove(format_buff, temp_buf, find_newline(temp_buf, len) + 1);
	*buffer = (char *)ft_calloc(len - find_newline(temp_buf, len) + 1, sizeof(char));
	if (!*buffer)
		return free_for_all(format_buff);
	ft_memmove(*buffer, temp_buf + find_newline(temp_buf, len) + 1, len - find_newline(temp_buf, len) - 1);
	free(temp_buf);
	return (format_buff);
}

char	*setup_new_buffer(char **buffer, int fd, long *offset)
{
	char	*temp_buf;

	if (*buffer == NULL)
	{
		*offset = 0;
		*buffer = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!*buffer)
			return NULL;
		if (read(fd, *buffer, BUFFER_SIZE) > 0)
			return *buffer;
		return NULL;
	}
	while ((*buffer)[*offset])
		(*offset)++;
	temp_buf = *buffer;
	*buffer = (char *)ft_calloc(BUFFER_SIZE + *offset + 1, sizeof(char));
	if (!*buffer)
		return free_for_all(temp_buf);
	ft_memmove(*buffer, temp_buf, *offset);
	free_for_all(temp_buf);
	read(fd, *buffer + *offset, BUFFER_SIZE);
	return *buffer;
}
