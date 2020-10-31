/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:33:31 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 20:07:00 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/scene.h"

t_scene		*new_scene(char *path)
{
	t_scene *result;

	if (!(result = malloc(sizeof(t_scene))))
		exit(EXIT_FAILURE);
	result->selected_camera_index = 0;
	result->amblight_lines_count = 0;
	result->resolution_lines_count = 0;
	result->cam_count = 0;
	result->l_count = 0;
	result->sp_count = 0;
	result->pl_count = 0;
	result->sq_count = 0;
	result->cy_count = 0;
	result->tr_count = 0;
	check_name(path);
	parse(path, result);
	result->destroy = scene_destructor;
	return (result);
}

void		check_name(const char *path)
{
	int i;

	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '.' && path[i + 1] == '.' && path[i + 2] == '/')
		{
			i = i + 3;
			continue;
		}
		else if (path[i] == '.')
			break ;
		i++;
	}
	if (i < 1 || path[i] == '\0')
		exit(1);
	if (path[i + 1] != 'r')
		exit(1);
	if (path[i + 2] != 't')
		exit(1);
	if (path[i + 3] != '\0')
		exit(1);
}

void		scene_destructor(t_scene *self)
{
	self->ambient_light->destroy(self->ambient_light);
	while (self->cam_count--)
		self->camera[self->cam_count]->destroy(self->camera[self->cam_count]);
	while (self->l_count--)
		self->light[self->l_count]->destroy(self->light[self->l_count]);
	while (self->sp_count--)
		self->sphere[self->sp_count]->destroy(self->sphere[self->sp_count]);
	while (self->pl_count--)
		self->plane[self->pl_count]->destroy(self->plane[self->pl_count]);
	while (self->sq_count--)
		self->square[self->sq_count]->destroy(self->square[self->sq_count]);
	while (self->cy_count--)
		self->cylinder[self->cy_count]->destroy(self->cylinder[self->cy_count]);
	while (self->tr_count--)
		self->triangle[self->tr_count]->destroy(self->triangle[self->tr_count]);
	free(self->camera);
	free(self->light);
	free(self->sphere);
	free(self->plane);
	free(self->square);
	free(self->cylinder);
	free(self->triangle);
	free(self);
}
