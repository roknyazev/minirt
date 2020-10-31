/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:48:36 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/26 16:02:49 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scene.h"

t_sphere		*parse_sphere(const char *line)
{
	int			i;
	double		*nmb;
	t_vec		*pos;
	t_color		*color;
	t_sphere	*result;

	i = 2;
	nmb = malloc(sizeof(double));
	pos = new_vector(0, 0, 0);
	color = new_color(0, 0, 0);
	i = i + skip_spaces(line + i);
	i = i + parse_pos(&line[i], pos);
	i = i + skip_spaces(line + i);
	i = i + ft_atof(&line[i], nmb);
	if (*nmb < 0.)
		raise_exception("Invalid radius of one of spheres", 33);
	i = i + skip_spaces(line + i);
	i = i + parse_color(&line[i], color);
	if (line[i] != '\0')
		raise_exception("Error in one of sphere lines", 29);
	result = new_sphere(pos, color, *nmb);
	free(nmb);
	return (result);
}

t_plane			*parse_plane(const char *line)
{
	int		i;
	t_vec	*pos;
	t_vec	*orient;
	t_color	*color;

	i = 2;
	orient = new_vector(0, 0, 0);
	pos = new_vector(0, 0, 0);
	color = new_color(0, 0, 0);
	i = i + skip_spaces(line + i);
	i = i + parse_pos(&line[i], pos);
	i = i + skip_spaces(line + i);
	i = i + parse_orient(&line[i], orient);
	i = i + skip_spaces(line + i);
	i = i + parse_color(&line[i], color);
	if (line[i] != '\0')
		raise_exception("Error in one of plane lines", 28);
	return (new_plane(pos, orient, color));
}

t_square		*parse_square(const char *line)
{
	int			i;
	t_vec		*pos;
	t_vec		*orient;
	t_color		*color;
	double		nmb;

	i = 2;
	orient = new_vector(0, 0, 0);
	pos = new_vector(0, 0, 0);
	color = new_color(0, 0, 0);
	i = i + skip_spaces(line + i);
	i = i + parse_pos(&line[i], pos);
	i = i + skip_spaces(line + i);
	i = i + parse_orient(&line[i], orient);
	i = i + skip_spaces(line + i);
	i = i + ft_atof(&line[i], &nmb);
	if (nmb < 0.)
		raise_exception("Invalid side size of one of squares", 36);
	i = i + skip_spaces(line + i);
	i = i + parse_color(&line[i], color);
	if (line[i] != '\0')
		raise_exception("Error in one of square lines", 29);
	return (new_square(pos, orient, color, nmb));
}

t_cylinder		*parse_cylinder(const char *line)
{
	int			i;
	t_vec		*pos;
	t_vec		*orient;
	t_color		*color;
	double		nmb;

	i = 2;
	orient = new_vector(0, 0, 0);
	pos = new_vector(0, 0, 0);
	color = new_color(0, 0, 0);
	i = i + skip_spaces(line + i);
	i = i + parse_pos(&line[i], pos);
	i = i + skip_spaces(line + i);
	i = i + parse_orient(&line[i], orient);
	i = i + skip_spaces(line + i);
	i = i + ft_atof(&line[i], &nmb);
	if (nmb < 0.)
		raise_exception("Invalid radius of one of cylinders", 35);
	i = i + skip_spaces(line + i);
	i = i + parse_color(&line[i], color);
	if (line[i] != '\0')
		raise_exception("Error in one of cylinder lines", 31);
	return (new_cylinder(pos, orient, color, nmb));
}

t_triangle		*parse_triangle(const char *line)
{
	int		i;
	t_vec	*pos1;
	t_vec	*pos2;
	t_vec	*pos3;
	t_color	*color;

	i = 2;
	pos1 = new_vector(0, 0, 0);
	pos2 = new_vector(0, 0, 0);
	pos3 = new_vector(0, 0, 0);
	color = new_color(0, 0, 0);
	i = i + skip_spaces(line + i);
	i = i + parse_pos(&line[i], pos1);
	i = i + skip_spaces(line + i);
	i = i + parse_pos(&line[i], pos2);
	i = i + skip_spaces(line + i);
	i = i + parse_pos(&line[i], pos3);
	i = i + skip_spaces(line + i);
	i = i + parse_color(&line[i], color);
	if (line[i] != '\0')
		raise_exception("Error in one of triangle lines", 31);
	return (new_triangle(pos1, pos2, pos3, color));
}
