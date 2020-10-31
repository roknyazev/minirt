/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 07:56:48 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/31 14:45:07 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raytrace.h"

t_vec			*base_cast(int cx, int cy, t_scene *scene, int camera_index)
{
	t_vec *result;

	result = new_vector(0, 0, 0);
	result->x = (double)cx - ((double)scene->res_x) / 2.;
	result->y = -(double)cy + ((double)scene->res_y) / 2.;
	result->z = scene->camera[camera_index]->distance_to_viewport;
	return (result);
}

t_vec			*ray_cast(int cx, int cy, t_scene *scene, int camera_index)
{
	t_vec	*tmp;
	t_vec	*right;
	t_vec	*up;
	t_vec	*dir;
	t_vec	*result;

	tmp = base_cast(cx, cy, scene, camera_index);
	result = new_vector(0, 0, 0);
	dir = scene->camera[camera_index]->orient;
	dir->product_by_scalar(dir, 1. / dir->magnitude(dir));
	up = new_vector(1e-100, 1, 1e-100);
	right = cross_product(up, dir);
	right->product_by_scalar(right, 1. / right->magnitude(right));
	up->destroy(up);
	up = cross_product(dir, right);
	up->product_by_scalar(up, 1. / up->magnitude(up));
	result->x = tmp->x * right->x + tmp->y * up->x + tmp->z * dir->x;
	result->y = tmp->x * right->y + tmp->y * up->y + tmp->z * dir->y;
	result->z = tmp->x * right->z + tmp->y * up->z + tmp->z * dir->z;
	tmp->destroy(tmp);
	right->destroy(right);
	up->destroy(up);
	return (result);
}

static void		set_normal_vec(t_flag *flag, t_vec *intersect_p,
							t_scene *scn, t_object *obj)
{
	if (obj->normal_vec != NULL)
		obj->normal_vec->destroy(obj->normal_vec);
	if (flag->type == 's')
		obj->normal_vec = scn->sphere[flag->index]->
				get_normal(scn->sphere[flag->index], intersect_p);
	else if (flag->type == 'p')
		obj->normal_vec = scn->plane[flag->index]->
				get_normal(scn->plane[flag->index]);
	else if (flag->type == 'c')
		obj->normal_vec = scn->cylinder[flag->index]->
				get_normal(scn->cylinder[flag->index], intersect_p);
	else if (flag->type == 'q')
		obj->normal_vec = scn->square[flag->index]->
				get_normal(scn->square[flag->index]);
	else if (flag->type == 't')
		obj->normal_vec = scn->triangle[flag->index]->
				get_normal(scn->triangle[flag->index]);
	else
		obj->normal_vec = NULL;
}

static void		set_color(t_flag *flag, t_scene *scene, t_object *object)
{
	if (flag->type == 's')
	{
		object->color = scene->sphere[flag->index]->color;
		object->specular = 1000;
		object->reflective = 0.3;
	}
	if (flag->type == 'p')
	{
		object->color = scene->plane[flag->index]->color;
		object->specular = 10000;
		object->reflective = 0.1;
	}

	if (flag->type == 'c')
	{
		object->color = scene->cylinder[flag->index]->color;
		object->specular = 10000;
		object->reflective = 0.1;
	}

	if (flag->type == 'q')
	{
		object->color = scene->square[flag->index]->color;
		object->specular = 100;
		object->reflective = 0.7;
	}

	if (flag->type == 't')
	{
		object->color = scene->triangle[flag->index]->color;
		object->specular = 100;
		object->reflective = 0.65;
	}
}

t_vec			*intersect(t_scene *scn, t_object *obj,
						t_vec *o, t_vec *d)
{
	t_vec		*result;
	t_flag		flag;

	result = new_vector(0, 0, 0);
	obj->exist = 0;
	flag.type = 0;
	flag.t = 1e100;
	int_with_sp(&flag, scn, o, d);
	int_with_pl(&flag, scn, o, d);
	int_with_cy(&flag, scn, o, d);
	int_with_sq(&flag, scn, o, d);
	int_with_tr(&flag, scn, o, d);
	if (flag.type != 0)
	{
		obj->exist = 1;
		obj->t = flag.t;
		d->product_by_scalar(d, flag.t);
		result = vec_sum(o, d, result);
	}
	set_color(&flag, scn, obj);
	set_normal_vec(&flag, result, scn, obj);
	return (result);
}
