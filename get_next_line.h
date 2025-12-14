/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturini <eturini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:32:55 by eturini           #+#    #+#             */
/*   Updated: 2025/12/14 17:51:17 by eturini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0

char	*get_next_line(int fd);
char	*read_new_line(int fd, char **stash);
char	*get_line(char **stash);
char	*set_next_stash(char **stash);
char	*ft_strjoin(char *s1, char *s2);
char	*free_for_all(char **buffer);
int		find_nl(char *s);

#endif
