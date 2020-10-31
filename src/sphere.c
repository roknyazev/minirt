/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 21:34:36 by wrudy             #+#    #+#             */
/*   Updated: 2020/10/25 19:52:40 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/objects.h"

t_sphere		*new_sphere(t_vec *pos, t_color *color, double d)
{
	t_sphere *result;

	if (!(result = malloc(sizeof(t_sphere))))
		exit(EXIT_FAILURE);
	result->pos = pos;
	result->color = color;
	result->diameter = d;
	result->intersection = sphere_intersection;
	result->get_normal = get_sphere_normal;
	result->destroy = sphere_destructor;
	return (result);
}

double			sphere_intersection(t_vec *o, t_vec *d, t_sphere *sphere)
{
	t_vec		*oc;
	double		k1;
	double		k2;
	double		k3;
	double		ds;

	oc = sphere->pos;
	oc = new_vector(o->x - oc->x, o->y - oc->y, o->z - oc->z);
	k1 = sc_mult(d, d);
	k2 = 2.0 * sc_mult(oc, d);
	k3 = sc_mult(oc, oc) - sphere->diameter / 2. * sphere->diameter / 2.;
	oc->destroy(oc);
	ds = k2 * k2 - 4. * k1 * k3;
	if (ds < 0.)
		return (1e100);
	return (choice((-k2 + sqrt(ds)) / (2. * k1), (-k2 - sqrt(ds)) / (2. * k1),
				1e-3, 1e100));
}

t_vec			*get_sphere_normal(struct s_sphere *self, t_vec *intersect_p)
{
	t_vec *result;

	result = new_vector(0, 0, 0);
	result = vec_diff(intersect_p, self->pos, result);
	result->product_by_scalar(result, 1. / result->magnitude(result));
	return (result);
}

void			sphere_destructor(t_sphere *self)
{
	self->pos->destroy(self->pos);
	self->color->destroy(self->color);
	free(self);
}
