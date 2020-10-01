/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 07:56:48 by wrudy             #+#    #+#             */
/*   Updated: 2020/09/30 00:05:49 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

t_vector	*ray_direction(int cx, int cy, t_scene *scene, int selected_camera)
{
	double		dx;
	double		dy;
	double		dz;
	double		m;
	t_vector	*camera_pos;
	t_vector	*result;

	camera_pos = scene->camera[selected_camera]->pos;

	dx = (double)cx - (((double)scene->resolution_x) / 2.);
	dy = -(double)cy + (((double)scene->resolution_y) / 2.);
	dz = scene->camera[selected_camera]->distance_to_viewport;
	result = new_vector(dx, dy, dz);
	m = result->magnitude(result);
	result->product_by_scalar(result, 1./m);
	return (result);
}

t_vector 			*intersection(t_scene *scene, t_object *object, t_vector *o, t_vector *d)
{
	int i;
	double t;
	int result_i;
	double solution;
	t_vector *result;

	result = new_vector(0, 0, 0);
	t = 1e100;
	object->exist = 0;
	i = 0;
	result_i = -1;
	while (i < scene->sphere_count)
	{
		solution = scene->sphere[i]->intersection(o, d, scene->sphere[i]);
		if (solution < t)
		{
			t = solution;
			result_i = i;
		}
		i++;
	}
	if (result_i >= 0)
	{
		object->exist = 1;
		object->specular = scene->sphere[result_i]->specular;
		object->reflect = scene->sphere[result_i]->reflective;
		object->color = scene->sphere[result_i]->color;
		object->t = t;
		d->product_by_scalar(d, t);
		result = vec_sum(o, d, result);
		object->normal_vec = scene->sphere[result_i]->get_normal(scene->sphere[result_i], result);

	}
	return (result);
}
