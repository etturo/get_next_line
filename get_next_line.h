/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturini <eturini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:32:55 by eturini           #+#    #+#             */
/*   Updated: 2025/12/11 13:28:29 by eturini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>

# define TRUE 1
# define FALSE 0

char	*get_next_line(int fd);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
long	find_newline(const char *s, size_t n);
char	*format_string(char *s);
char	*setup_next_line(char *s);
char	*setup_new_buffer(char *buffer, size_t *offset, int fd);

#endif
