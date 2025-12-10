/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eturini <eturini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:33:00 by eturini           #+#    #+#             */
/*   Updated: 2025/12/10 18:58:51 by eturini          ###   ########.fr       */
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

size_t	find_newline(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (s[i] != EOF && i < n)
	{
		if (s[i] == '\n')
			return i;
		i++;
	}
	return FALSE;
}

char	*format_string(char *s)
{
	char	*form_str;
	size_t	i;

	i = 0;
	while (s[i] != EOF && s[i] != '\n')
		i++;
	form_str = (char *)ft_calloc(i + 1, sizeof(char));
	if (!form_str)
		return NULL;
	ft_memmove(form_str, s, i);
	if (s[i] == EOF)
		free(s);
	return form_str;
}
