/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:03:28 by wrudy             #+#    #+#             */
/*   Updated: 2020/07/24 21:44:53 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static int	safety_return(int flag, char *mem1, char *mem2, char *mem3)
{
	if (mem1 != NULL)
		free(mem1);
	if (mem2 != NULL)
		free(mem2);
	if (mem3 != NULL && flag != 0)
		free(mem3);
	return (flag);
}

static int	process_surplus(char **out, char **surplus)
{
	char *tmp;

	if (*surplus != NULL)
	{
		if (!(tmp = gnl_strjoin("", *surplus)))
			return (safety_return(-1, *surplus, 0, 0));
		free(*surplus);
		if ((*surplus = gnl_strchr(tmp, '\n')))
		{
			*surplus[0] = '\0';
			if (!(*surplus = gnl_strjoin("", *surplus + 1)))
				return (safety_return(-1, tmp, 0, 0));
			*out = gnl_strjoin("", tmp);
		}
		else
			*out = gnl_strjoin("", tmp);
		free(tmp);
	}
	else
		*out = gnl_calloc(1, sizeof(char));
	if (!*out)
		return (safety_return(-1, *surplus, 0, 0));
	return (1);
}

static int	reading(int fd, char **out, char **s)
{
	char	*tmp;
	char	*tmp1;
	int		tmp_len;

	while (!*s)
	{
		if (!(tmp = gnl_calloc(BUFFER_SIZE + 1, sizeof(char))))
			return (-1);
		if ((tmp_len = read(fd, tmp, BUFFER_SIZE)) < 1)
			return (safety_return(tmp_len, tmp, *s, *out));
		if ((*s = gnl_strchr(tmp, '\n')))
		{
			*s[0] = '\0';
			if (!(*s = gnl_strjoin("", *s + 1)))
				return (safety_return(-1, tmp, *s, *out));
		}
		tmp1 = *out;
		if (!(*out = gnl_strjoin(*out, tmp)))
			return (safety_return(-1, tmp, *s, tmp1));
		free(tmp);
		free(tmp1);
	}
	return (1);
}

int			get_next_line(int fd, char **line)
{
	static char		*surplus;
	char			*out;
	int				flag;

	if ((flag = process_surplus(&out, &surplus)) < 1)
		return (flag);
	if (surplus == NULL)
		if ((flag = reading(fd, &out, &surplus)) < 0)
			return (flag);
	*line = out;
	return (flag);
}
