/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturini <eturini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:43:51 by eturini           #+#    #+#             */
/*   Updated: 2025/12/15 16:27:49 by eturini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*new_s;

	len1 = 0;
	if (s1)
		while (s1[len1])
			len1++;
	len2 = 0;
	while (s2[len2])
		len2++;
	new_s = malloc(len1 + len2 + 1);
	if (!new_s)
		return ((void *)0);
	i = -1;
	while (++i < len1)
		new_s[i] = s1[i];
	i -= 1;
	while (++i < len1 + len2)
		new_s[i] = s2[i - len1];
	new_s[len1 + len2] = '\0';
	free(s1);
	return (new_s);
}

long	find_nl(char *s)
{
	long	i;

	if (!s)
		return (-1);
	i = -1;
	while (s[++i])
		if (s[i] == '\n')
			return (i);
	return (-1);
}

char	*free_for_all(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}
