/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 16:05:07 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/26 16:12:31 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scene.h"

int		ft_atof(const char *nptr, double *nmb)
{
	double	n;
	double	after_dot;
	double	divider;
	int		i;

	i = 0;
	divider = 1;
	n = (float)ft_atoi(nptr);
	while (ft_isdigit(nptr[i]) || nptr[i] == '-')
		i++;
	if (nptr[i] != '.' || !ft_isdigit(nptr[i + 1]))
	{
		*nmb = n;
		return (i);
	}
	after_dot = ft_atoi(&nptr[++i]);
	while (ft_isdigit(nptr[i]))
	{
		divider = divider * 10;
		i++;
	}
	*nmb = n + (after_dot / divider);
	if (nptr[0] == '-')
		*nmb = n - (after_dot / divider);
	return (i);
}

int		parse_pos(const char *line, t_vec *pos)
{
	int		i;
	double	*nmb;

	nmb = malloc(sizeof(double));
	i = ft_atof(line, nmb);
	pos->x = *nmb;
	if (line[i] != ',' || !(ft_isdigit(line[i + 1]) || line[i + 1] == '-'))
		raise_exception("Error while reading one of position vector", 43);
	i = i + ft_atof(&line[i + 1], nmb) + 1;
	pos->y = *nmb;
	if (line[i] != ',' || !(ft_isdigit(line[i + 1]) || line[i + 1] == '-'))
		raise_exception("Error while reading one of position vector", 43);
	i = i + ft_atof(&line[i + 1], nmb) + 1;
	pos->z = *nmb;
	if (line[i] != ' ' && line[i] != '\t' && line[i] != '\0')
		raise_exception("Error while reading one of position vector", 43);
	free(nmb);
	return (i);
}

int		parse_orient(const char *line, t_vec *orient)
{
	int i;

	i = parse_pos(line, orient);
	if (orient->x > 1.0 || orient->x < -1.0)
		raise_exception("Error while reading one of orientation vector", 46);
	if (orient->y > 1.0 || orient->y < -1.0)
		raise_exception("Error while reading one of orientation vector", 46);
	if (orient->z > 1.0 || orient->z < -1.0)
		raise_exception("Error while reading one of orientation vector", 46);
	return (i);
}

int		parse_color(const char *line, t_color *color)
{
	int i;
	int nmb;

	i = 0;
	nmb = ft_atoi(line);
	color->rgb_color->x = (double)nmb;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i++] != ',' || !ft_isdigit(line[i]))
		raise_exception("Error while reading one of color", 33);
	nmb = ft_atoi(&line[i]);
	color->rgb_color->y = (double)nmb;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i++] != ',' || !ft_isdigit(line[i]))
		raise_exception("Error while reading one of color", 33);
	nmb = ft_atoi(&line[i]);
	color->rgb_color->z = (double)nmb;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] == ' ' || line[i] == '\t' || line[i] == '\0')
		return (i);
	raise_exception("Error while reading one of color", 33);
	return (0);
}

void	raise_exception(const char *exception_text, unsigned count)
{
	write(2, exception_text, count);
	exit(EXIT_FAILURE);
}
