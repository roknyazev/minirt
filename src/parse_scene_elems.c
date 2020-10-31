/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_elems.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:36:55 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/26 15:57:11 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scene.h"

void		parse_resolution(const char *line, t_scene *scene)
{
	int i;

	i = 2;
	i = i + skip_spaces(line + i);
	if (!ft_isdigit(line[i]))
		raise_exception("Error in resolution line", 31);
	scene->res_x = ft_atoi(&line[i]);
	if (scene->res_x < 150)
		raise_exception("Resolution width is too small", 30);
	if (scene->res_x > MAX_RESOLUTION_X)
		scene->res_x = MAX_RESOLUTION_X;
	while (ft_isdigit(line[i]))
		i++;
	i = i + skip_spaces(line + i);
	if (!ft_isdigit(line[i]))
		raise_exception("Error in resolution line", 31);
	scene->res_y = ft_atoi(&line[i]);
	if (scene->res_y < 100)
		raise_exception("Resolution height is too small", 31);
	if (scene->res_y > MAX_RESOLUTION_Y)
		scene->res_y = MAX_RESOLUTION_Y;
	while (ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0')
		raise_exception("Error in resolution line", 31);
}

t_camera	*parse_camera(const char *line)
{
	int			i;
	double		*nmb;
	t_vec		*pos;
	t_vec		*orient;
	t_camera	*result;

	i = 2;
	nmb = malloc(sizeof(double));
	pos = new_vector(0, 0, 0);
	orient = new_vector(0, 0, 0);
	i = i + skip_spaces(line + i);
	i = i + parse_pos(&line[i], pos);
	i = i + skip_spaces(line + i);
	i = i + parse_orient(&line[i], orient);
	i = i + skip_spaces(line + i);
	i = i + ft_atof(&line[i], nmb);
	if (*nmb > 180. || *nmb < 0)
		raise_exception("Incorrect FOV value", 20);
	if (line[i] != '\0')
		raise_exception("Error in one of camera lines", 29);
	result = new_camera(pos, orient, *nmb);
	free(nmb);
	return (result);
}

t_amblight	*parse_amblight(const char *line)
{
	int			i;
	double		*nmb;
	t_color		*color;
	t_amblight	*result;

	i = 2;
	nmb = malloc(sizeof(double));
	i = i + skip_spaces(line + i);
	i = i + ft_atof(&line[i], nmb);
	if (*nmb < 0 || *nmb > 1)
		raise_exception("Invalid ambient light brightness", 33);
	i = i + skip_spaces(line + i);
	if (!ft_isdigit(line[i]))
		raise_exception("Error in ambient light line", 28);
	color = new_color(0, 0, 0);
	i = i + parse_color(&line[i], color);
	if (line[i] != '\0')
		raise_exception("Error in ambient light line", 28);
	result = new_amblight(color, *nmb);
	free(nmb);
	return (result);
}

t_light		*parse_light(const char *line)
{
	int			i;
	double		*nmb;
	t_vec		*pos;
	t_color		*color;
	t_light		*result;

	i = 2;
	nmb = malloc(sizeof(double));
	pos = new_vector(0, 0, 0);
	color = new_color(0, 0, 0);
	i = i + skip_spaces(line + i);
	i = i + parse_pos(&line[i], pos);
	i = i + skip_spaces(line + i);
	i = i + ft_atof(&line[i], nmb);
	if (*nmb > 1. || *nmb < 0.)
		raise_exception("Invalid brightness of one of lights", 36);
	i = i + skip_spaces(line + i);
	i = i + parse_color(&line[i], color);
	if (line[i] != '\0')
		raise_exception("Error in one of light lines", 28);
	result = new_light(pos, color, *nmb);
	free(nmb);
	return (result);
}
