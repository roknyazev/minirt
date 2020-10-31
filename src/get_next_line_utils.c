/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 18:11:40 by wrudy             #+#    #+#             */
/*   Updated: 2020/07/24 21:43:55 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void			*gnl_calloc(size_t nmemb, size_t size)
{
	char	*s;
	size_t	i;

	if ((s = malloc(nmemb * size)) == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		s[i] = '\0';
		i++;
	}
	return (s);
}

static size_t	gnl_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char			*gnl_strchr(const char *s, int c)
{
	size_t i;

	i = 0;
	if (c == '\0')
		return ((char *)(s + gnl_strlen(s)));
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

static char		*gnl_strcpy(char *dest, const char *src)
{
	size_t i;

	i = 0;
	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}

char			*gnl_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len_s1;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = gnl_strlen(s1);
	if ((res = malloc((len_s1 + gnl_strlen(s2) + 1) * sizeof(char))) == NULL)
		return (NULL);
	gnl_strcpy(res, s1);
	gnl_strcpy(res + len_s1, s2);
	return (res);
}
