/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 18:48:29 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/27 22:49:30 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raytrace.h"
# define DEPTH 5

static t_vec *reflect_ray(t_vec *r, t_vec *n)
{
	double tmp;
	t_vec *result;

	result = new_vector(0, 0, 0);
	tmp = 2 * sc_mult(n, r);
	multiplication_by_scalar(n, tmp, result);
	vec_diff(result, r, result);
	return (result);
}

static double	light_br(t_light *light, t_vec *n, t_vec *l, char channel)
{
	double result;

	if (channel == 'r')
		result = light->brightness * (light->color->rgb_color->x / 255.);
	else if (channel == 'g')
		result = light->brightness * (light->color->rgb_color->y / 255.);
	else if (channel == 'b')
		result = light->brightness * (light->color->rgb_color->z / 255.);
	else
		result = 0.;
	return (result / (n->magnitude(n) * l->magnitude(l)));
}

static void		bright_calc(t_vec *bright, t_vec *p, t_vec *n, t_scene *scene, t_object *object, t_vec *v)
{
	int			i;
	double		ang;
	t_vec		*l;
	t_object	*shadow_object;
	t_vec 		*r;
	double tmp;

	i = scene->l_count;
	l = new_vector(0., 0., 0.);
	shadow_object = new_object();
	while (i--)
	{
		l = vec_diff(scene->light[i]->pos, p, l);
		vector_destructor(intersect(scene, shadow_object, p, l));
		if (shadow_object->exist && shadow_object->t < 1)
			continue;
		ang = sc_mult(n, l);
		if (ang > 0)
		{
			bright->x = bright->x + light_br(scene->light[i], n, l, 'r') * ang;
			bright->y = bright->y + light_br(scene->light[i], n, l, 'g') * ang;
			bright->z = bright->z + light_br(scene->light[i], n, l, 'b') * ang;
		}
		if (object->specular > 0)
		{
			r = reflect_ray(l, n);

			tmp = sc_mult(r, v);
			if (tmp < 0)
			{
				tmp = scene->light[i]->brightness *
					  pow(tmp / (r->magnitude(r) * v->magnitude(v)), object->specular);
				bright->x = bright->x + tmp;
				bright->y = bright->y + tmp;
				bright->z = bright->z + tmp;
			}
		}
		r->destroy(r);
	}
	l->destroy(l);
	shadow_object->destroy(shadow_object);
}

static t_color	*virtual_color(t_object *obj, t_vec *p, t_vec *n, t_scene *scn, t_vec *v)
{
	t_vec		*bright;
	t_color		*result;
	double		amb_ratio;

	amb_ratio = scn->ambient_light->ratio;
	bright = new_vector(0, 0, 0);
	bright->x = amb_ratio * scn->ambient_light->color->rgb_color->x / 255.;
	bright->y = amb_ratio * scn->ambient_light->color->rgb_color->y / 255.;
	bright->z = amb_ratio * scn->ambient_light->color->rgb_color->z / 255.;
	bright_calc(bright, p, n, scn, obj, v);
	result = new_color(
			obj->color->rgb_color->x * bright->x,
			obj->color->rgb_color->y * bright->y,
			obj->color->rgb_color->z * bright->z);
	bright->destroy(bright);
	return (result);
}

static t_color	*trace(t_vec *o, t_vec *d, t_scene *scene, int depth)
{
	t_object	*object;
	t_vec		*intersection_point;
	t_color 	*local_color;
	t_color		*result;
	t_vec		*norm;
	t_vec		*r;
	double 		reflective;
	t_color		*reflected_color;

	object = new_object();
	intersection_point = intersect(scene, object, o, d);
	if (!(object->exist))
	{
		object->destroy(object);
		intersection_point->destroy(intersection_point);
		return (new_color(0., 0., 0.));
	}
	norm = object->normal_vec;
	if (sc_mult(norm, d) > 0)
		norm->product_by_scalar(norm, -1.);
	local_color = virtual_color(object, intersection_point, norm, scene, d);

	reflective = object->reflective;
	if (reflective <= 0 || depth <= 0)
	{
		object->destroy(object);
		intersection_point->destroy(intersection_point);
		return (local_color);
	}

	d->product_by_scalar(d, -1);
	r = reflect_ray(d, object->normal_vec);
	reflected_color = trace(intersection_point, r, scene, depth - 1);

	local_color->rgb_color->product_by_scalar(local_color->rgb_color, 1 - reflective);
	reflected_color->rgb_color->product_by_scalar(reflected_color->rgb_color, reflective * ((double)depth / (double)DEPTH));
	result = new_color(0, 0, 0);
	vec_sum(local_color->rgb_color, reflected_color->rgb_color, result->rgb_color);

	local_color->destroy(local_color);
	reflected_color->destroy(reflected_color);
	object->destroy(object);
	intersection_point->destroy(intersection_point);
	return (result);
}

t_color			*raytrace(int cnv_x, int cnv_y, t_scene *scene, int cam_ind)
{
	t_vec	*d;
	t_vec	*o;
	t_color	*result;
	int	depth;

	depth = DEPTH;
	d = ray_cast(cnv_x, cnv_y, scene, cam_ind);
	d->product_by_scalar(d, 1. / d->magnitude(d));
	o = scene->camera[cam_ind]->pos;
	result = trace(o, d, scene, depth);
	d->destroy(d);
	return (result);
}
