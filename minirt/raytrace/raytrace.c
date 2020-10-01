/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 18:48:29 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/01 19:11:48 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "stdio.h"

static t_vector *reflect_ray(t_vector *r, t_vector *n)
{
	double tmp;
	t_vector *result;

	if (!(result = new_vector(0, 0, 0)))
		return (NULL);
	tmp = 2 * scalar_multiplication(n, r);
	multiplication_by_scalar(n, tmp, result);
	vec_diff(result, r, result);
	return (result);
}

t_color *object_color(t_object *object, t_vector *p, t_vector *n, t_scene *scene, t_vector *v)
{
	int i;
	double tmp;
	double bright;
	t_color *result;
	t_vector *r;
	t_vector *l;
	t_object *shadow_object;

	shadow_object = new_object();
	bright = scene->ambient_light->ratio;
	l = new_vector(0, 0, 0);
	i = 0;
	while (i < scene->lights_count)
	{
		l = vec_diff(scene->light[i]->pos, p, l);
		intersection(scene, shadow_object, p, l);
		if (shadow_object->exist && shadow_object->t < 1)
		{
			i++;
			continue;
		}
		tmp = scalar_multiplication(n, l);
		if (tmp > 0)
			bright = bright + scene->light[i]->brightness * tmp / (n->magnitude(n) * l->magnitude(l));
		if (object->specular > 0)
		{
			r = reflect_ray(l, n);
			tmp = scalar_multiplication(r, v);
			if (tmp < 0)
				bright = bright + scene->light[i]->brightness *
						pow(tmp / (r->magnitude(r) * v->magnitude(v)), object->specular);
		}
		i++;
	}
	result = new_color(object->color->rgb_color->x * bright,
					   object->color->rgb_color->y * bright,
					   object->color->rgb_color->z * bright);
	return (result);
}

t_color			*trace(t_vector *o, t_vector *d, t_scene *scene, int depth)
{
	t_color		*local_color;
	t_color		*reflected_color;
	t_color		*result;
	t_vector	*intersection_point;
	t_object	*object;
	t_vector	*r;

	object = new_object();
	intersection_point = intersection(scene, object, o, d);
	if (!(object->exist))
	{
		object->destroy(object);
		intersection_point->destroy(intersection_point);
		return (new_color(0, 0, 0));
	}
	local_color = object_color(object, intersection_point, object->normal_vec, scene, d); //FIXME 5 arg
	if (depth <= 0 || object->reflect <= 0)
	{
		object->destroy(object);
		intersection_point->destroy(intersection_point);
		return local_color;
	}
	d->product_by_scalar(d, -1);
	r = reflect_ray(d, object->normal_vec);
	reflected_color = trace(intersection_point, r, scene, depth - 1);
	r->destroy(r);
	intersection_point->destroy(intersection_point);
	local_color->rgb_color->product_by_scalar(local_color->rgb_color, 1. - object->reflect);
	reflected_color->rgb_color->product_by_scalar(reflected_color->rgb_color, object->reflect);
	object->destroy(object);
	result = new_color(0, 0, 0);
	vec_sum(local_color->rgb_color, reflected_color->rgb_color, result->rgb_color);
	local_color->destroy(local_color);
	reflected_color->destroy(reflected_color);
	return (result);
}

t_color			*raytrace(int canvas_x, int canvas_y, t_scene *scene, int selected_camera)
{
	t_vector	*d;
	t_vector	*o;
	t_color		*result;

	d = ray_direction(canvas_x, canvas_y, scene, selected_camera);
	o = scene->camera[selected_camera]->pos;
	result = trace(o, d, scene, 3);
	d->destroy(d);
	return (result);
}
